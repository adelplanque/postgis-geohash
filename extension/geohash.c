/**********************************************************************
 *
 * Postgis-Geohash
 * Copyright 2017, 2021 Alain Delplanque
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 *
 **********************************************************************/

#include <math.h>
#include <postgres.h>
#include <fmgr.h>
#if PG_MAJORVERSION_NUM >= 16
#include <varatt.h>
#endif
#include "../ext/postgis/liblwgeom/liblwgeom.h"

#define PG_GETARG_GSERIALIZED_P(varno) ((GSERIALIZED *)PG_DETOAST_DATUM(PG_GETARG_DATUM(varno)))

PG_MODULE_MAGIC;

/** Table de conversion base32 */
static const char *base32 = "0123456789bcdefghjkmnpqrstuvwxyz";
int64 mk_geohash(const POINT2D *p, int deep);
int64 mk_reverse_geohash(const POINT2D *p, int deep);


/**
 * Calcul d'un geohash sur 60 bits avec une profondeur donnée
 */
int64 mk_geohash(const POINT2D *p, int deep) {
    int x_res = deep / 2 + deep % 2;
    int y_res = deep / 2;

    int64 fact = (uint64) 1 << 30;
    int64 x = (unsigned int) floor((p->x + 180.0) / 360.0 * fact);
    int64 y = (unsigned int) floor((p->y + 90.0) / 180.0 * fact);

    int64 geohash = 0;
    int64 mask = (uint64) 1 << 29;
    int i;

    for (i = 0; i < 30; i++) {
        geohash = geohash << 1;
        if (i < x_res) {
            geohash |= (x & mask) ? 1 : 0;
        }
        geohash = geohash << 1;
        if (i < y_res) {
            geohash |= (y & mask) ? 1 : 0;
        }
        mask = mask >> 1;
    }

    return geohash;
}


/**
 * Calcul d'un geohash sur 60 bits avec une profondeur donnée
 */
int64 mk_reverse_geohash(const POINT2D *p, int deep) {
    int x_res = deep / 2 + deep % 2;
    int y_res = deep / 2;

    int64 fact = (uint64) 1 << 30;
    int64 x = (unsigned int) floor((p->x + 180.0) / 360.0 * fact);
    int64 y = (unsigned int) floor((p->y + 90.0) / 180.0 * fact);

    int64 geohash = 0;
    int64 mask = (uint64) 1 << 29;
    int64 h_bit = (uint64) 1 << 59;
    int i;

    for (i = 0; i < 30; i++) {
        geohash = geohash >> 1;
        if (i < x_res) {
            geohash |= (x & mask) ? h_bit : 0;
        }
        geohash = geohash >> 1;
        if (i < y_res) {
            geohash |= (y & mask) ? h_bit : 0;
        }
        mask = mask >> 1;
    }

    return geohash;
}


PG_FUNCTION_INFO_V1(GeohashAsInt64);
/**
 * Calcul d'un geohash sur 60 bits et retourne le résultat sous forme entière (int64)
 * Le bit de poids 2^59 contient la première division du dmaine
 */
Datum GeohashAsInt64(PG_FUNCTION_ARGS) {
    GSERIALIZED *geom = PG_GETARG_GSERIALIZED_P(0);
    LWGEOM *lwgeom = lwgeom_from_gserialized(geom);
    int deep = PG_GETARG_INT32(1);
    POINT2D p;
    int64 geohash;

	if (deep < 0 || lwgeom_is_empty(lwgeom) || lwgeom->type != POINTTYPE) {
		PG_RETURN_NULL();
    }

    if (deep > 60) {
        deep = 60;
    }

    getPoint2d_p(((LWPOINT*) lwgeom)->point, 0, &p);

    if (p.x < -180 || p.x > 180 || p.y < -90 || p.y > 90) {
		PG_RETURN_NULL();
    }

    geohash = mk_geohash(&p, deep);

    PG_RETURN_INT64(geohash);
}


PG_FUNCTION_INFO_V1(ReverseGeohashAsInt64);
/**
 * Calcul d'un geohash sur 60 bits et retourne le résultat sous forme entière (int64)
 * Le bit de poids 2^0 contient la première division du dmaine
 */
Datum ReverseGeohashAsInt64(PG_FUNCTION_ARGS) {
    GSERIALIZED *geom = PG_GETARG_GSERIALIZED_P(0);
    LWGEOM *lwgeom = lwgeom_from_gserialized(geom);
    int deep = PG_GETARG_INT32(1);
    POINT2D p;
    int64 geohash;

	if (deep < 0 || lwgeom_is_empty(lwgeom) || lwgeom->type != POINTTYPE) {
		PG_RETURN_NULL();
    }

    if (deep > 60) {
        deep = 60;
    }

    getPoint2d_p(((LWPOINT*) lwgeom)->point, 0, &p);

    if (p.x < -180 || p.x > 180 || p.y < -90 || p.y > 90) {
		PG_RETURN_NULL();
    }

    geohash = mk_reverse_geohash(&p, deep);

    PG_RETURN_INT64(geohash);
}


PG_FUNCTION_INFO_V1(GeohashAsText);
/**
 * Calcul d'un geohah sur 60 bits et retourne le résultat en base32 sur le nombre minimal de caractères.
 */
Datum GeohashAsText(PG_FUNCTION_ARGS) {
    GSERIALIZED *geom = PG_GETARG_GSERIALIZED_P(0);
    LWGEOM *lwgeom = lwgeom_from_gserialized(geom);
    int deep = PG_GETARG_INT32(1);
    POINT2D p;
    int digits;
    char geohash[13];
    int64 geohash_int;
    text* result;
    size_t result_size;
    int i;

	if (deep < 0 || lwgeom_is_empty(lwgeom) || lwgeom->type != POINTTYPE) {
		PG_RETURN_NULL();
    }

    if (deep > 60) {
        deep = 60;
    }

    getPoint2d_p(((LWPOINT*) lwgeom)->point, 0, &p);

    if (p.x < -180 || p.x > 180 || p.y < -90 || p.y > 90) {
		PG_RETURN_NULL();
    }

    digits = ((deep - 1) / 5) + 1;

    geohash_int = mk_geohash(&p, deep);

    for (i = 0; i < digits; i++) {
        int shift = (11 - i) * 5;
        int idx = (geohash_int >> shift) & 0x1F;
        geohash[i] = base32[idx];
    }
    geohash[digits] = 0;

    result_size = digits + 1 + VARHDRSZ;
    result = palloc(result_size);
    SET_VARSIZE(result, result_size);
    memcpy(VARDATA(result), geohash, digits + 1);

    PG_RETURN_TEXT_P(result);
}

dnl **********************************************************************
dnl *
dnl * Postgis-Geohash
dnl * Copyright 2017, 2021 Alain Delplanque
dnl *
dnl * This program is free software: you can redistribute it and/or modify
dnl * it under the terms of the GNU General Public License as published by
dnl * the Free Software Foundation, either version 3 of the License, or
dnl * (at your option) any later version.
dnl *
dnl * This program is distributed in the hope that it will be useful,
dnl * but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl * GNU General Public License for more details.
dnl *
dnl * You should have received a copy of the GNU General Public License
dnl * along with this program.  If not, see <https://www.gnu.org/licenses/>
dnl *
dnl **********************************************************************

AC_PREREQ([2.69])
AC_INIT([postgis-geohash], [0.1.1])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h ext/postgis/postgis_config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])

AC_PROG_CC

dnl We need gcc-ar and gcc-ranlib in order to use LTO
AC_ARG_VAR([AR], [AR command (default is gcc-ar)])
AC_CHECK_TOOL([AR], [gcc-ar])
AC_ARG_VAR([RANLIB], [RANLIB command (default is gcc-ranlib)])
AC_CHECK_TOOL([RANLIB], [gcc-ranlib])

dnl LIBTOOL
AM_PROG_AR
LT_INIT

dnl Types
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T

dnl Postgresql

AC_ARG_WITH(
    [pg-config],
    [AS_HELP_STRING([--with-pg-config=/path/to/pg_config], [Path to pg_config program for the PostgreSQL installation to build against])],
    [PG_CONFIG=$(realpath $withval)
     AS_IF([test ! -x ${PG_CONFIG}],
           [AC_MSG_ERROR([Invalid pg_config: ${PG_CONFIG}])])],
    [AC_PATH_PROG([PG_CONFIG], [pg_config])
     AS_IF([test "${PG_CONFIG}" = ""],
           [AC_MSG_ERROR([Unable to find pg_config])])])

AC_SUBST([PG_CONFIG])

PG_FULL_VERSION=`$PG_CONFIG --version`

PGXS=$(${PG_CONFIG} --pgxs)
AS_IF(
    [test "x$PGXS" = "x" -o ! -f "$PGXS"],
    [AC_MSG_ERROR([the PGXS Makefile $PGXS cannot be found. Please install the PostgreSQL server development packages and re-run configure.])]
)
AC_SUBST(PGXS)

PG_PKGLIBDIR="$(${PG_CONFIG} --pkglibdir)"
PG_SHAREDIR="$(${PG_CONFIG} --sharedir)"


dnl ===========================================================================
dnl Minimal postgis setup in order to build liblwgeom
dnl ===========================================================================

AC_DEFINE_UNQUOTED([POSTGIS_GEOS_VERSION], [39], [Embeded GEOS version])
AC_DEFINE_UNQUOTED([POSTGIS_PROJ_VERSION], [81], [Embeded PROJ version])
SRID_MAX=999999
SRID_USR_MAX=998999
AC_SUBST([SRID_MAX])
AC_SUBST([SRID_USR_MAX])

dnl Generate output

AC_CONFIG_FILES([
    Makefile
    ext/Makefile
    ext/postgis/liblwgeom/liblwgeom.h
    extension/Makefile
    extension/postgis_geohash.control
    tests/install-check.sh
    ],
    [chmod +x tests/install-check.sh]
)


dnl Generate output files

AC_OUTPUT

dnl Configuration status

AC_MSG_RESULT()
AC_MSG_RESULT([  Geohash configure complete])
AC_MSG_RESULT()
AC_MSG_RESULT([  PostgreSQL config:    ${PG_CONFIG}])
AC_MSG_RESULT([  PostgreSQL version:   ${PG_FULL_VERSION}])

dnl Explain our prefix policy if necessary.

AS_IF([test "$prefix" != "NONE"],
[
  AC_MSG_RESULT()
  AC_MSG_RESULT([------------------------------------------------------------------------])
  AC_MSG_RESULT([  WARNING: You have set the --prefix to '$prefix'. But we mostly    ])
  AC_MSG_RESULT([  ignore the --prefix. For your info, using the values determined from ])
  AC_MSG_RESULT([  $PG_CONFIG we will be installing:   ])
  AC_MSG_RESULT([    * postgis_geohash shared library in ${PG_PKGLIBDIR} ])
  AC_MSG_RESULT([    * postgis_geohash SQL files in ${PG_SHAREDIR}/extension ])
  AC_MSG_RESULT([------------------------------------------------------------------------])
])

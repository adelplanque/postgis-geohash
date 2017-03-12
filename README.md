## Postgis-Geohash ##

Postgis-Geohash is an extension for Postgres / Postgis to calculate per bit precision geohash.

It use 64 bits integer for store up to 60 bits geohash (12 digits in base32 common format).


## Install ##

Build of Postgis-Geohash need Postgis sources.

### From repository sources ###

    autoreconf --install
    ./configure --with-postgis=path/to/postgis/sources
    make
    [make check]
    make install
    [make installcheck]

### From source archive ###

    tar -xzf geohash-x.y.z.tar.gz
    ./configure --with-postgis=path/to/postgis/sources
    make
    [make check]
    make install
    [make installcheck]


## Usage ##

### Load extension ###

    CREATE EXTENSION postgis;
    CREATE EXTENSION postgis_geohash;

### Fonctions ###

#### GoeohashAsInt64 ####

    FUNCTION GeohashAsInt64(geom geometry, deep int4 DEFAULT 64)
    RETURNS INT8

If `geometry` is a POINT geometry, compute geohash, return `NULL` value for others geometries.
Geohash is encoding over bits 2^59 to 2^(59-deep+1).
Bit 2^59 is for the first split according to latitude, bit 2^58 for the first split according to longitude.

Over bits are set to 0.

#### GeohashAsText ####

    FUNCTION GeohashAsText(geom geometry, deep int4 DEFAULT 64)
	RETURNS TEXT

If `geometry` is a POINT geometry, compute geohash, return `NULL` value for others geometries.
Like `GeohashAsInt64` but result is converted to a base 32.
Right zeros are truncated.

If `geom` is a POINT:

    GeohastAsText(geom, digits * 5) == ST_Geohash(geom, digits)

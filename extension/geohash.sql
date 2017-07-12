CREATE OR REPLACE FUNCTION GeohashAsInt64(geom geometry, deep int4 DEFAULT 64)
	RETURNS INT8
		AS '$libdir/postgis_geohash.so', 'GeohashAsInt64'
	LANGUAGE 'c' IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION ReverseGeohashAsInt64(geom geometry, deep int4 DEFAULT 64)
	RETURNS INT8
		AS '$libdir/postgis_geohash.so', 'ReverseGeohashAsInt64'
	LANGUAGE 'c' IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION GeohashAsText(geom geometry, deep int4 DEFAULT 64)
	RETURNS TEXT
		AS '$libdir/postgis_geohash.so', 'GeohashAsText'
	LANGUAGE 'c' IMMUTABLE STRICT;

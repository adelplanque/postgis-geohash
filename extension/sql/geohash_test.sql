CREATE EXTENSION postgis;
CREATE EXTENSION postgis_geohash;

SELECT GeohashAsInt64(ST_GeomFromText('POINT(10 20)'), 7);
SELECT GeohashAsText(ST_GeomFromText('POINT(10 20)'), 7);
SELECT GeohashAsInt64(ST_GeomFromText('LINESTRING(10 20, 30 40)'), 7);
SELECT GeohashAsText(ST_GeomFromText('LINESTRING(10 20, 30 40)'), 7);

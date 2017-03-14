# -*- coding: utf-8 -*-

import os
import psycopg2
import testing.postgresql
import unittest

top_srcdir = os.path.dirname(os.path.dirname(__file__))
geohash_so = os.path.join(top_srcdir, 'extension', 'postgis_geohash.so')
geohash_sql = os.path.join(top_srcdir, 'extension', 'geohash.sql')


def postgresql_init(postgresql):
    con = psycopg2.connect(**postgresql.dsn())
    cursor = con.cursor()
    cursor.execute("CREATE EXTENSION postgis;")
    con.commit()
    cursor.close()
    con.close()


Postgresql = testing.postgresql.PostgresqlFactory(
    cache_initialized_db=True,
    on_initialized=postgresql_init
)


class PostgresqlMixIn(object):
    """
    Provide postgresql testing environnement.
    """

    def setUp(self):
        self.postgres = Postgresql()
        self.con = psycopg2.connect(**self.postgres.dsn())
        self.cursor = self.con.cursor()

    def execute_and_fetchall(self, sql):
        print("SQL: %s" % sql)
        try:
            self.cursor.execute(sql)
            return self.cursor.fetchall()
        except:
            with open(os.path.join(self.postgres.base_dir,
                                   'Postgresql.log'), 'r') as infile:
                print(infile.read())
            raise

    def tearDown(self):
        self.cursor.close()
        self.con.close()
        self.postgres.stop()


class TestPostgisVersion(PostgresqlMixIn, unittest.TestCase):
    """
    Simple test to print postgis version.
    """

    def test_postgis_version(self):
        sql = "SELECT PostGIS_full_version();"
        data = self.execute_and_fetchall(sql)
        print("Postgis: %s" % str(data))


class TestGeohash(PostgresqlMixIn, unittest.TestCase):
    """
    Test Geohash functions.
    """

    def setUp(self):
        super(TestGeohash, self).setUp()
        self.load_geohash_extension()

    def load_geohash_extension(self):
        print("Load geohash")
        with open(geohash_sql, 'r') as infile:
            sql = infile.read()
        sql = sql.replace('$libdir/postgis_geohash.so', geohash_so)
        print(sql)
        self.cursor.execute(sql)
        self.con.commit()

    def tearDown(self):
        self.cursor.close()
        self.con.close()
        self.postgres.stop()

    def test_geohash_int64(self):
        sql = "SELECT ST_GeomFromText('POINT(10 20)')"
        self.execute_and_fetchall(sql)

        data = self.execute_and_fetchall(sql)
        geom = "ST_GeomFromText('POINT(10 20)')"
        sql = "SELECT GeohashAsInt64(%s, 7)" % geom
        data = self.execute_and_fetchall(sql)
        value = data[0][0]
        self.assertEquals(value, 864691128455135232)

    def test_geohash_text_50(self):
        geom = "ST_GeomFromText('POINT(45 20)')"
        sql = "SELECT GeohashAsText(%s, 50)" % geom
        data = self.execute_and_fetchall(sql)
        value = data[0][0]
        self.assertEquals(value, 't581b0bh2n')

    def test_geohash_text_6(self):
        geom = "ST_GeomFromText('POINT(45 20)')"
        sql = "SELECT GeohashAsText(%s, 6)" % geom
        data = self.execute_and_fetchall(sql)
        value = data[0][0]
        self.assertEquals(value, 't0')

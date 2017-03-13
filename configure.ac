AC_PREREQ([2.13])
AC_INIT([Postgis-Geohash], [0.1.0])
EXT_NAME=postgis_geohash
AC_SUBST([EXT_NAME])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

dnl Compilateurs
AC_PROG_CC

dnl Autre programmes
AM_PROG_AR

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

PG_BIN="$(${PG_CONFIG} --bindir)"
AC_SUBST([PG_BIN])
PG_LIB="$(${PG_CONFIG} --libdir)"
AC_SUBST([PG_LIB])
PG_SHAREDIR="$(${PG_CONFIG} --sharedir)"
PG_PKGLIBDIR="$(${PG_CONFIG} --pkglibdir)"

dnl liblwgeom

AC_CHECK_HEADERS(
    [liblwgeom.h],
    [],
    [AC_MSG_ERROR([Unable to find liblwgeom.h])]
)

AC_CHECK_LIB(
    [lwgeom],
    [lwgeom_from_gserialized],
    [POSTGIS_LIB="-llwgeom"
     AC_SUBST([POSTGIS_LIB])],
    [AC_MSG_ERROR([Unable to find liblwgeom])]
)

dnl Generate output

AC_CONFIG_FILES([
    Makefile
    extension/Makefile
    extension/postgis_geohash.control
    m4/Makefile
    nosetests.py
    tests/Makefile
    ])

dnl Python

PC_INIT([2.7], [3.5.99])

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
  AC_MSG_RESULT([    * geohash shared library in ${PG_PKGLIBDIR} ])
  AC_MSG_RESULT([    * geohash SQL files in ${PG_SHAREDIR}/extension ])
  AC_MSG_RESULT([------------------------------------------------------------------------])
])

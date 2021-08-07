noinst_LTLIBRARIES = liblwgeom.la

liblwgeom_la_CFLAGS = -Iproj/src -Igeos/capi -Igeos/include -Ipostgis/deps \
	-flto -ffunction-sections -fdata-sections

liblwgeom_la_LDFLAGS = -Wl,-flto

liblwgeom_la_SOURCES = \
	postgis/liblwgeom/bytebuffer.c \
	postgis/liblwgeom/bytebuffer.h \
	postgis/liblwgeom/effectivearea.c \
	postgis/liblwgeom/effectivearea.h \
	postgis/liblwgeom/gbox.c \
	postgis/liblwgeom/gserialized.c \
	postgis/liblwgeom/gserialized.h \
	postgis/liblwgeom/gserialized1.c \
	postgis/liblwgeom/gserialized1.h \
	postgis/liblwgeom/gserialized2.c \
	postgis/liblwgeom/gserialized2.h \
	postgis/liblwgeom/liblwgeom.h \
	postgis/liblwgeom/liblwgeom_internal.h \
	postgis/liblwgeom/lookup3.c \
	postgis/liblwgeom/lwalgorithm.c \
	postgis/liblwgeom/lwboundingcircle.c \
	postgis/liblwgeom/lwchaikins.c \
	postgis/liblwgeom/lwcircstring.c \
	postgis/liblwgeom/lwcollection.c \
	postgis/liblwgeom/lwcompound.c \
	postgis/liblwgeom/lwcurvepoly.c \
	postgis/liblwgeom/lwgeodetic.c \
	postgis/liblwgeom/lwgeodetic.h \
	postgis/liblwgeom/lwgeodetic_tree.c \
	postgis/liblwgeom/lwgeodetic_tree.h \
	postgis/liblwgeom/lwgeom.c \
	postgis/liblwgeom/lwgeom_api.c \
	postgis/liblwgeom/lwgeom_debug.c \
	postgis/liblwgeom/lwgeom_log.h \
	postgis/liblwgeom/lwgeom_median.c \
	postgis/liblwgeom/lwgeom_transform.c \
	postgis/liblwgeom/lwhomogenize.c \
	postgis/liblwgeom/lwin_encoded_polyline.c \
	postgis/liblwgeom/lwin_geojson.c \
	postgis/liblwgeom/lwin_twkb.c \
	postgis/liblwgeom/lwin_wkb.c \
	postgis/liblwgeom/lwin_wkt.c \
	postgis/liblwgeom/lwin_wkt.h \
	postgis/liblwgeom/lwin_wkt_lex.c \
	postgis/liblwgeom/lwin_wkt_parse.c \
	postgis/liblwgeom/lwin_wkt_parse.h \
	postgis/liblwgeom/lwinline.h \
	postgis/liblwgeom/lwiterator.c \
	postgis/liblwgeom/lwkmeans.c \
	postgis/liblwgeom/lwline.c \
	postgis/liblwgeom/lwlinearreferencing.c \
	postgis/liblwgeom/lwmcurve.c \
	postgis/liblwgeom/lwmline.c \
	postgis/liblwgeom/lwmpoint.c \
	postgis/liblwgeom/lwmpoly.c \
	postgis/liblwgeom/lwmsurface.c \
	postgis/liblwgeom/lwmval.c \
	postgis/liblwgeom/lwout_encoded_polyline.c \
	postgis/liblwgeom/lwout_geojson.c \
	postgis/liblwgeom/lwout_gml.c \
	postgis/liblwgeom/lwout_kml.c \
	postgis/liblwgeom/lwout_svg.c \
	postgis/liblwgeom/lwout_twkb.c \
	postgis/liblwgeom/lwout_twkb.h \
	postgis/liblwgeom/lwout_wkb.c \
	postgis/liblwgeom/lwout_wkt.c \
	postgis/liblwgeom/lwout_x3d.c \
	postgis/liblwgeom/lwout_x3d.h \
	postgis/liblwgeom/lwpoint.c \
	postgis/liblwgeom/lwpoly.c \
	postgis/liblwgeom/lwpsurface.c \
	postgis/liblwgeom/lwrandom.c \
	postgis/liblwgeom/lwrandom.h \
	postgis/liblwgeom/lwspheroid.c \
	postgis/liblwgeom/lwstroke.c \
	postgis/liblwgeom/lwtin.c \
	postgis/liblwgeom/lwtree.c \
	postgis/liblwgeom/lwtree.h \
	postgis/liblwgeom/lwtriangle.c \
	postgis/liblwgeom/lwunionfind.c \
	postgis/liblwgeom/lwunionfind.h \
	postgis/liblwgeom/lwutil.c \
	postgis/liblwgeom/measures.c \
	postgis/liblwgeom/measures.h \
	postgis/liblwgeom/measures3d.c \
	postgis/liblwgeom/measures3d.h \
	postgis/liblwgeom/ptarray.c \
	postgis/liblwgeom/stringbuffer.c \
	postgis/liblwgeom/stringbuffer.h \
	postgis/liblwgeom/varint.c \
	postgis/liblwgeom/varint.h \
	postgis/postgis_revision.h \
	proj/src/geodesic.h \
	proj/src/proj.h

BUILT_SOURCES = \
	postgis/postgis_revision.h

EXTRA_DIST = \
	postgis/COPYING \
	postgis/LICENSE.TXT \
	proj/COPYING

postgis/postgis_revision.h:
	echo "#define POSTGIS_REVISION \"embded.$(shell git -C postgis describe --always)\"" > $@

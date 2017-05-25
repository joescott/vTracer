TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../vTrazer
HEADERS         = rkhparsermodel.h
SOURCES         = rkhparsermodel.cpp
TARGET          = $$qtLibraryTarget(rkhparsermodel)
DESTDIR         = ../../vTrazer/plugins/models

DISTFILES += \
    test/tzparse.log \
    test/tzsim.py

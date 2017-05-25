TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../vTrazer
HEADERS         = rkhparsermodel.h \
    moc_predefs.h
SOURCES         = rkhparsermodel.cpp \
    moc_rkhparsermodel.cpp
TARGET          = $$qtLibraryTarget(rkhparsermodel)
DESTDIR         = ../../vTrazer/plugins/models

DISTFILES += \
    test/tzparse.log \
    test/tzsim.py

#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T17:19:55
#
#-------------------------------------------------
#include(../third_party/common/common.pri)
#include(../third_party/5waybutton/5waybutton.pri)
#include(../third_party/basicdialgauge/basicdialgauge.pri)
#include(../third_party/basicgraph/basicgraph.pri)
#include(../third_party/multislider/multislider.pri)
#include(../third_party/scrolldial/scrolldial.pri)
#include(../third_party/scrollwheel/scrollwheel.pri)
#include(../third_party/svgbutton/svgbutton.pri)
#include(../third_party/svgdialgauge/svgdialgauge.pri)
#include(../third_party/svgslideswitch/svgslideswitch.pri)
#include(../third_party/svgtoggleswitch/svgtoggleswitch.pri)

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vTrazer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generalconf.cpp \
    filter.cpp \
    util.cpp \
    sessionmanager.cpp \
    runconf.cpp \
    runapp.cpp \
    output.cpp \
    proxymodel.cpp \
    columnfilter.cpp \
    loadfileprogressbar.cpp \
    itemtool.cpp \
    filtertool.cpp \
    watchtool.cpp \
    watch.cpp \
    watchview.cpp \
    grapher.cpp \
    graphwindow.cpp

HEADERS  += mainwindow.h \
    def.h \
    generalconf.h \
    filter.h \
    util.h \
    sessionmanager.h \
    runconf.h \
    runapp.h \
    output.h \
    echointerface.h \
    itemDelegate.h \
    proxymodel.h \
    columnfilter.h \
    loadfileprogressbar.h \
    parsermodelinterface.h \
    modelfilterdefinition.h \
    itemtool.h \
    filtertool.h \
    watchtool.h \
    watch.h \
    modelwatchdefinition.h \
    actioninterface.h \
    watchview.h \
    grapher.h \
    graphwindow.h

FORMS    += mainwindow.ui \
    generalconf.ui \
    filter.ui \
    sessionmanager.ui \
    runconf.ui \
    runapp.ui \
    output.ui \
    columnfilter.ui \
    loadfileprogressbar.ui \
    itemtool.ui \
    watch.ui \
    watchview.ui \
    grapher.ui \
    graphwindow.ui

RESOURCES += \
    vTrazer.qrc

RESOURCES += ../third_party/skins/thermometer_svgdialgauge.qrc \
    ../third_party/skins/tachometer_svgdialgauge.qrc \
    ../third_party/skins/amperemeter_svgdialgauge.qrc \
    ../third_party/skins/beryl_5waybutton.qrc \
    ../third_party/skins/beryl_multislider.qrc \
    ../third_party/skins/beryl_svgslideswitch.qrc \
    ../third_party/skins/beryl_svgbutton.qrc \
    ../third_party/skins/beryl_svgtoggleswitch.qrc \
    ../third_party/skins/berylsquare_svgtoggleswitch.qrc \
    ../third_party/skins/berylsquare_svgbutton.qrc \
    ../third_party/skins/beryl_scrollwheel.qrc \
    ../third_party/skins/beryl_scrolldial.qrc \
    ../third_party/skins/metallicbrush_svgbutton.qrc \
    ../third_party/skins/metallicbrush_svgslideswitch.qrc \
    ../third_party/iuskins/iuskins.qrc

OTHER_FILES += \
    conf.ini

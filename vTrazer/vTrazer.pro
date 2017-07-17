#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T17:19:55
#
#-------------------------------------------------
QT       += core gui svg charts

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
    graphwindow.cpp \
    rkheventview.cpp \
    callout.cpp \
    configurationcontainer.cpp

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
    graphwindow.h \
    callout.h \
    rkheventview.h \
    eventserie.h \
    configurationcontainer.h

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
    graphwindow.ui \
    configurationcontainer.ui

RESOURCES += \
    vTrazer.qrc

OTHER_FILES += \
    conf.ini

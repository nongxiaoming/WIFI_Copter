TEMPLATE = lib
TARGET = ExtensionSystem
DEFINES += EXTENSIONSYSTEM_LIBRARY

include(../../common.pri)


unix:!macx:!freebsd*:LIBS += -ldl

DEFINES += GCS_TEST_DIR=\\\"$$GCS_SOURCE_TREE\\\"

QT +=  core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += pluginerrorview.h \
    plugindetailsview.h \
    iplugin.h \
    iplugin_p.h \
    extensionsystem_global.h \
    pluginmanager.h \
    pluginmanager_p.h \
    pluginspec.h \
    pluginspec_p.h \
    pluginview.h \
    pluginview_p.h \
    optionsparser.h
SOURCES += pluginerrorview.cpp \
    plugindetailsview.cpp \
    iplugin.cpp \
    pluginmanager.cpp \
    pluginspec.cpp \
    pluginview.cpp \
    optionsparser.cpp
FORMS += pluginview.ui \
    pluginerrorview.ui \
    plugindetailsview.ui
RESOURCES += pluginview.qrc

#指定生成的lib保存目录
DESTDIR=$$PROJECT_LIBRARYDIR

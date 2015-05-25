# -------------------------------------------------
# QGroundStation - a Groundstation for coper
# Maintainer:
# nongxiaoming <nongxiaoming@gmail.com>
# (c) 2014 QGroundStation Developers
# This file is part of the QGroundStation project
# QGroundStation is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# QGroundStation is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with QGroundControl. If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------

include(../common.pri)
# Qt configuration
CONFIG += qt \
         thread

QT       += core gui\
         opengl \
          svg \
           xml \
          sql \
          declarative\
          network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = QGroundStation
TEMPLATE = app

win32 {
    RC_FILE = groundstation.rc
    target.path = /bin
    INSTALLS += target
} else:macx {
    LIBS += -framework CoreFoundation
    ICON = groundstation.icns
    QMAKE_INFO_PLIST = Info.plist
    FILETYPES.files = profile.icns prifile.icns
    FILETYPES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += FILETYPES
} else {
    target.path  = /bin
    INSTALLS    += target
}

OTHER_FILES += groundstation.rc \
    groundstation.pro.user

RESOURCES += \
    groundstation.qrc


SOURCES += main.cpp\
PrimaryFlightDisplay.cpp \
    modelviewwidget.cpp \
    copterctrlpage.cpp \
    coptersettingpage.cpp \
    discoverpage.cpp \
    plotingpage.cpp \
    statuspage.cpp \
    upgradepage.cpp \
    content_widget.cpp \
    xmainwindow.cpp\
    xtitlewidget.cpp \
    xframe/character_widget.cpp \
    xframe/system_tray.cpp \
    xframe/util.cpp \
    xframe/xlabel.cpp \
    xframe/xmainmenu.cpp \
    xframe/xpushbutton.cpp \
    xframe/xskinitem.cpp \
    xframe/xskinmanager.cpp \
    xframe/xskinwidget.cpp \
    xframe/xtoolbutton.cpp \
    meterwidget.cpp

    xframe/xtoolbutton.cpp

HEADERS  += PrimaryFlightDisplay.h \
    modelviewwidget.h \
    copterctrlpage.h \
    coptersettingpage.h \
    discoverpage.h \
    plotingpage.h \
    statuspage.h \
    upgradepage.h \
    xtitlewidget.h \
    content_widget.h \
    xmainwindow.h\
    xframe/character_widget.h \
    xframe/common.h \
    xframe/resource.h \
    xframe/system_tray.h \
    xframe/util.h \
    xframe/xlabel.h \
    xframe/xmainmenu.h \
    xframe/xpushbutton.h \
    xframe/xskinitem.h \
    xframe/xskinmanager.h \
    xframe/xskinwidget.h \
    xframe/xtoolbutton.h \
    meterwidget.h



FORMS    += \
    copterctrlpage.ui \
    coptersettingpage.ui \
    discoverpage.ui \
    plotingpage.ui \
    statuspage.ui \
    upgradepage.ui

INCLUDEPATH +=.


LIBS +=-l$$qtLibraryName(QCustomPlot)\
       -l$$qtLibraryName(ExtensionSystem)\
       -l$$qtLibraryName(Utils)\
       -l$$qtLibraryName(GLC_lib)

DESTDIR=$${PROJECT_BINDIR}

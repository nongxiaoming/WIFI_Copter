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
          webkit \
          sql \
          declarative\
          network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGroundStation
TEMPLATE = app

win32 {
    RC_FILE = openpilotgcs.rc
    target.path = /bin
    INSTALLS += target
} else:macx {
    LIBS += -framework CoreFoundation
    ICON = openpilotgcs.icns
    QMAKE_INFO_PLIST = Info.plist
    FILETYPES.files = profile.icns prifile.icns
    FILETYPES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += FILETYPES
} else {
    target.path  = /bin
    INSTALLS    += target
}

OTHER_FILES += openpilotgcs.rc

RESOURCES += \
    appresources.qrc


SOURCES += main.cpp\
        mainwindow.cpp\
PrimaryFlightDisplay.cpp

HEADERS  += mainwindow.h\
PrimaryFlightDisplay.h


FORMS    += mainwindow.ui

INCLUDEPATH +=.


LIBS +=-l$$qtLibraryName(QChart)\
       -l$$qtLibraryName(ExtensionSystem)\
       -l$$qtLibraryName(Utils)


DESTDIR=$${PROJECT_BINDIR}

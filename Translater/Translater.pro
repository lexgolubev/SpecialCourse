#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T20:56:34
#
#-------------------------------------------------

QT       -= gui

TARGET = Translater
TEMPLATE = lib

DEFINES += TRANSLATER_LIBRARY

SOURCES += translater.cpp \
    db.cpp \
    Main.cpp \
    Lang.cpp

HEADERS += translater.h\
        translater_global.h \
    db.h \
    Lang.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

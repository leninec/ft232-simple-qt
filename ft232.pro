#-------------------------------------------------
#
# Project created by QtCreator 2021-11-26T14:02:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ft232
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ftdi.cpp

HEADERS  += widget.h \
    ftd2xx.h \
    ftdi.h



FORMS    += widget.ui

RC_FILE = myappico.rc



win32: LIBS += -L$$PWD/ -lftd2xx

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32: PRE_TARGETDEPS += $$PWD/ftd2xx.lib

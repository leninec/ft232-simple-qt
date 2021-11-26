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
        widget.cpp

HEADERS  += widget.h \
    ftd2xx.h


FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lftd2xx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lftd2xxd

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ftd2xx.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ftd2xxd.lib

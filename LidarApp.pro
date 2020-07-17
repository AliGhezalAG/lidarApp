#-------------------------------------------------
#
# Project created by QtCreator 2019-09-04T13:58:00
#
#-------------------------------------------------

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LidarApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        hometab.cpp \
        lidarapp.cpp \
        main.cpp \
        qortexclient.cpp \
        zonetab.cpp \
        header.cpp \
        object.cpp \
        objectpacket.cpp \
        shape.cpp \
        triplet.cpp \
        vertice.cpp \
        zone.cpp \
        zonepacket.cpp

HEADERS += \
        config.h \
        hometab.h \
        lidarapp.h \
        qortexclient.h \
        zonetab.h \
        header.h \
        object.h \
        objectpacket.h \
        shape.h \
        triplet.h \
        vertice.h \
        zone.h \
        zonepacket.h

#FORMS += \
#        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# OpenCV
INCLUDEPATH += /usr/local/include/opencv4/opencv2
LIBS += $(shell pkg-config opencv --libs)

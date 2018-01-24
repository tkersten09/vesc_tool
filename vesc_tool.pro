#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T21:55:19
#
#-------------------------------------------------

# Version
VT_VERSION = 0.87
VT_INTRO_VERSION = 1

# Use static linking for deploying a standalone executable for a release
CONFIG+= static

DEFINES += VT_VERSION=$$VT_VERSION
DEFINES += VT_INTRO_VERSION=$$VT_INTRO_VERSION

# Serial port available
DEFINES += HAS_SERIALPORT

# Options
#CONFIG += build_original
#CONFIG += build_platinum
#CONFIG += build_gold
#CONFIG += build_silver
#CONFIG += build_bronze
#CONFIG += build_free

# Build mobile GUI
#CONFIG += build_mobile

#CONFIG += qtquickcompiler

QT       += core gui
QT       += widgets
QT       += printsupport
QT       += network
QT       += bluetooth
QT       += quick
QT       += quickcontrols2

contains(DEFINES, HAS_SERIALPORT) {
    QT       += serialport
}

android: QT += androidextras

android: TARGET = vesc_tool
!android: TARGET = vesc_tool_$$VT_VERSION

TEMPLATE = app

release_win {
    DESTDIR = build/win
    OBJECTS_DIR = build/win/obj
    MOC_DIR = build/win/obj
    RCC_DIR = build/win/obj
    UI_DIR = build/win/obj
}

release_lin {
    # http://micro.nicholaswilson.me.uk/post/31855915892/rules-of-static-linking-libstdc-libc-libgcc
    # http://insanecoding.blogspot.se/2012/07/creating-portable-linux-binaries.html
    QMAKE_LFLAGS += -static-libstdc++ -static-libgcc
    DESTDIR = build/lin
    OBJECTS_DIR = build/lin/obj
    MOC_DIR = build/lin/obj
    RCC_DIR = build/lin/obj
    UI_DIR = build/lin/obj
}

release_android {
    DESTDIR = build/android
    OBJECTS_DIR = build/android/obj
    MOC_DIR = build/android/obj
    RCC_DIR = build/android/obj
    UI_DIR = build/android/obj
}

build_mobile {
    DEFINES += USE_MOBILE
}

SOURCES += main.cpp\
        mainwindow.cpp \
    packet.cpp \
    vbytearray.cpp \
    commands.cpp \
    configparams.cpp \
    configparam.cpp \
    vescinterface.cpp \
    parametereditor.cpp \
    digitalfiltering.cpp \
    setupwizardapp.cpp \
    setupwizardmotor.cpp \
    startupwizard.cpp \
    bleuart.cpp \
    utility.cpp

HEADERS  += mainwindow.h \
    packet.h \
    vbytearray.h \
    commands.h \
    datatypes.h \
    configparams.h \
    configparam.h \
    vescinterface.h \
    parametereditor.h \
    digitalfiltering.h \
    setupwizardapp.h \
    setupwizardmotor.h \
    startupwizard.h \
    bleuart.h \
    utility.h

FORMS    += mainwindow.ui \
    parametereditor.ui

include(pages/pages.pri)
include(widgets/widgets.pri)
include(mobile/mobile.pri)

RESOURCES += res.qrc

build_original {
    RESOURCES += res_original.qrc \
    res_fw_original.qrc
    DEFINES += VER_ORIGINAL
} else:build_platinum {
    RESOURCES += res_platinum.qrc \
    res_fw.qrc
    DEFINES += VER_PLATINUM
} else:build_gold {
    RESOURCES += res_gold.qrc \
    res_fw.qrc
    DEFINES += VER_GOLD
} else:build_silver {
    RESOURCES += res_silver.qrc \
    res_fw.qrc
    DEFINES += VER_SILVER
} else:build_bronze {
    RESOURCES += res_bronze.qrc \
    res_fw.qrc
    DEFINES += VER_BRONZE
} else:build_free {
    RESOURCES += res_free.qrc \
    res_fw.qrc
    DEFINES += VER_FREE
} else {
    RESOURCES += res_neutral.qrc \
    res_fw.qrc
    DEFINES += VER_NEUTRAL
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

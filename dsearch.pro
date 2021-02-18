QT += core gui widgets

CONFIG += c++2a

INCLUDEPATH += ./include
MOC_DIR = ./moc
OBJECTS_DIR = ./obj
UI_DIR = ./ui

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/mainwindow.hpp

FORMS += \
    forms/mainwindow.ui

LIBS += -lfmt

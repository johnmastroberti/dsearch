QT += core gui widgets concurrent

CONFIG += c++2a

INCLUDEPATH += ./include
MOC_DIR = ./moc
OBJECTS_DIR = ./obj
UI_DIR = ./ui

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/searchengine.cpp

HEADERS += \
    include/mainwindow.hpp \
    include/searchengine.hpp

FORMS += \
    forms/mainwindow.ui

LIBS += -lfmt

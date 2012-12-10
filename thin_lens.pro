#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T20:25:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = thin_lens
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arrow.cpp \
    thin_lens_widget/thinlenssystem.cpp

HEADERS  += mainwindow.hpp \
    arrow.hpp \
    thin_lens_widget/thinlenssystem.hpp \
    thin_lens_widget/abstractobject.hpp

QMAKE_CXXFLAGS += -std=c++0x

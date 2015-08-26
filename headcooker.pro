#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T10:50:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = headcooker
TEMPLATE = app
LIBS += -lcurl
LIBS += -lsqlite3

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        Headcookerwindow.cpp \
    Curler.cpp \
    RecipeWidget.cpp \
    RecipeApiParser.cpp \
    xml/XMLTreeObject.cpp \
    FlowLayout.cpp \
    Recipe.cpp

HEADERS  += Headcookerwindow.h \
    Curler.h \
    RecipeWidget.h \
    RecipeApiParser.h \
    xml/XMLTree.h \
    xml/XMLTreeObject.h \
    FlowLayout.h \
    Recipe.h

FORMS    += Headcookerwindow.ui \
    RecipeWidget.ui

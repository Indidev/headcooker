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
    frontend/Headcookerwindow.cpp \
    frontend/RecipeWidget.cpp \
    frontend/FlowLayout.cpp \
    frontend/RecipeChooser.cpp \
    backend/Curler.cpp \
    backend/RecipeApiParser.cpp \
    backend/xml/XMLTreeObject.cpp \
    backend/Recipe.cpp \
    backend/database/DataRow.cpp \
    backend/database/Database.cpp \
    backend/DataTypes.cpp

HEADERS  += frontend/Headcookerwindow.h \
    frontend/RecipeWidget.h \
    frontend/FlowLayout.h \
    frontend/RecipeChooser.h \
    backend/Curler.h \
    backend/RecipeApiParser.h \
    backend/xml/XMLTree.h \
    backend/xml/XMLTreeObject.h \
    backend/Recipe.h \
    backend/database/DataRow.h \
    backend/database/Database.h \
    backend/DataTypes.h

FORMS    += frontend/Headcookerwindow.ui \
    frontend/RecipeWidget.ui \
    frontend/RecipeChooser.ui

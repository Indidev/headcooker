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
    backend/DataTypes.cpp \
    frontend/ExtendedButton.cpp \
    frontend/ExtendedLineEdit.cpp \
    backend/Options.cpp \
    frontend/menu/StyleMenu.cpp \
    frontend/menu/OptionsMenu.cpp \
    backend/Util.cpp \
    backend/FirefoxParser.cpp \
    frontend/menu/ImportMenu.cpp \
    frontend/MultiTagInput.cpp \
    frontend/CheckBoxBar.cpp

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
    backend/DataTypes.h \
    frontend/ExtendedButton.h \
    frontend/ExtendedLineEdit.h \
    backend/Options.h \
    frontend/menu/StyleMenu.h \
    frontend/menu/OptionsMenu.h \
    frontend/menu/MenuWidget.h \
    backend/Util.h \
    backend/FirefoxParser.h \
    frontend/menu/ImportMenu.h \
    frontend/MultiTagInput.h \
    frontend/CheckBoxBar.h

FORMS    += frontend/Headcookerwindow.ui \
    frontend/RecipeWidget.ui \
    frontend/RecipeChooser.ui \
    frontend/menu/StyleMenu.ui \
    frontend/menu/OptionsMenu.ui \
    frontend/menu/ImportMenu.ui \
    frontend/MultiTagInput.ui \
    frontend/CheckBoxBar.ui

# Define copy command for linux and windows
QMAKE_COPY = cp -rf
Win32:QMAKE_COPY = copy /y

# cp(src, dest) returns the copy command
defineReplace(cp) {
    SDIR = $$PWD/$$1
    DDIR = $$OUT_PWD/$$2

    # Replace slashes in paths with backslashes for Windows
    win32:DDIR ~= s,/,\\,g
    win32:SDIR ~= s,/,\\,g

    return($$QMAKE_COPY $$SDIR $$DDIR;)
}

#Directorys to create
DIRS = style \
       img/recipe

#Loop over all given directories and append
#the build directory to make absolute paths
for(DIR, DIRS) {

     #append directorys to base dir
     mkcommands += $$OUT_PWD/$$DIR
}

#make a custom createDir variable with
#the command mkdir path1 path2 path3 ...
createDirs.commands = $(MKDIR) $$mkcommands

cpFiles.commands += $$cp(style/*, style/)
cpFiles.commands += $$cp(img/*, img/)

#Add dependencies to first
first.depends += createDirs
first.depends += cpFiles

#add dependencies to makefile
QMAKE_EXTRA_TARGETS += first createDirs cpFiles

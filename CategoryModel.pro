#-------------------------------------------------
#
# Project created by MuratCAN 2017-10-05T10:37:36 ;)
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CategoryModel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp \
    menu.cpp \
    category.cpp \
    window.cpp 

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h \
    menu.h \
    category.h \
    window.h

RESOURCES +=

FORMS += \
    mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2013-09-01T10:12:58
#
#-------------------------------------------------

QT       += core gui
CONFIG += qdbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kstlinkGui
TEMPLATE = app

SOURCES += main.cpp

include (gui/gui.pro)
include (tray/tray.pro)
include (treePages/widgetTreePages.pro)


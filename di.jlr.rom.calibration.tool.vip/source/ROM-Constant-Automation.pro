#-------------------------------------------------
#
# Project created by QtCreator 2018-11-09T16:21:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = romcalibtool
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


SOURCES += \
    App/cfg_generator/cfg_generator.cpp \
    App/jlr_xml_parser/jlr_xml_parser.cpp \
    App/main_window/main_window.cpp \
    App/main.cpp \
    App/map_file_data/map_file_data.cpp \
    App/vbf_generator/vbf_generator.cpp

HEADERS += \
    App/cfg_generator/cfg_generator.h \
    App/error_handler/error_codes.h \
    App/jlr_xml_parser/jlr_xml_parser.h \
    App/main_window/main_window.h \
    App/rom_data_type/rom_data_types.h \
    App/map_file_data/map_file_data.h \
    App/vbf_generator/vbf_generator.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH += $$PWD/App

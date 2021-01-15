#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T08:24:23
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SPIRT_KIS_ZAYAVKY
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    mychild_nio_form.cpp \
    pole_nio.cpp \
    document_nio_year.cpp \
    vybor_documenta.cpp \
    model_nio_document.cpp \
    neispolsovany.cpp \
    delegate_nio_table.cpp \
    mychild_norma_form.cpp \
    base_my_child_form.cpp \
    model_norma_document.cpp \
    delegate_norma_table.cpp \
    pole_norma.cpp \
    document_norma.cpp \
    printpagenio.cpp \
    printpagenorma.cpp

HEADERS  += mainwindow.h \
    mychild_nio_form.h \
    pole_nio.h \
    document_nio_year.h \
    vybor_documenta.h \
    model_nio_document.h \
    delegate_nio_table.h \
    mychild_norma_form.h \
    base_my_child_form.h \
    model_norma_document.h \
    delegate_norma_table.h \
    pole_norma.h \
    document_norma.h \
    printpagenio.h \
    printpagenorma.h

FORMS    += mainwindow.ui \
    mychild_nio_form.ui \
    vybor_documenta.ui \
    mychild_norma_form.ui

RESOURCES += \
    res.qrc

DISTFILES +=

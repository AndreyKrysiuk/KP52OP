#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T13:27:42
#
#-------------------------------------------------

QT       += svg multimedia core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        guitartuner.cpp \
    fft.cpp \
    voiceanalyzer.cpp \
    voicegenerator.cpp

HEADERS  += guitartuner.h \
    fft.h \
    voiceanalyzer.h \
    voicegenerator.h

FORMS    += \
    guitartuner.ui

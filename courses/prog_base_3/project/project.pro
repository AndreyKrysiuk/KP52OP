#-------------------------------------------------
#
# Project created by QtCreator 2016-06-11T12:08:52
#
#-------------------------------------------------

QT       += multimedia core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        guitartuner.cpp \
    fft.cpp \
    voiceanalyzer.cpp \
    voicegenerator.cpp \
    fftpack.c

HEADERS  += guitartuner.h \
    fft.h \
    voiceanalyzer.h \
    voicegenerator.h

FORMS    += guitartuner.ui

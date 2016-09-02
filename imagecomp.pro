#-------------------------------------------------
#
# Project created by QtCreator 2016-09-02T08:45:04
#
#-------------------------------------------------

QT       += core gui

TARGET = imagecomp
TEMPLATE = app

INCLUDEPATH += /usr/include

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_video -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_flann
LIBS += -lopencv_features2d -lopencv_calib3d -lopencv_ml -lopencv_legacy -lopencv_photo -lopencv_gpu -lopencv_ocl -lopencv_nonfree


SOURCES += main.cpp \
    comparison.cpp

HEADERS += \
    comparison.h

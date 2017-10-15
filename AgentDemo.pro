#-------------------------------------------------
#
# Project created by QtCreator 2015-12-29T11:50:28
#
#-------------------------------------------------

QT       += core gui
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AgentDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CAgent.cpp \
    CMsKm.cpp \
    CRmKm.cpp \
    CScene.cpp \
    CView.cpp \
    CEnterWizard.cpp \
    CIntDelegate.cpp \
    CFloatDelegate.cpp \
    CSceneXml.cpp \
    CKm.cpp \
    CKmXml.cpp \
    CKmInfoWidget.cpp \
    CKmMatrixTWidget.cpp \
    CProcessWidget.cpp \
    CJwKm.cpp

HEADERS  += mainwindow.h \
    CAgent.h \
    CMsKm.h \
    CRmKm.h \
    CScene.h \
    CView.h \
    CEnterWizard.h \
    CIntDelegate.h \
    CFloatDelegate.h \
    CSceneXml.h \
    CKm.h \
    CKmXml.h \
    CKmInfoWidget.h \
    CKmMatrixTWidget.h \
    CProcessWidget.h \
    CJwKm.h

RESOURCES += \
    images.qrc

FORMS +=

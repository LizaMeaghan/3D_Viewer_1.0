QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/3D_Viewer_1_0/Line.cpp \
    ../src/3D_Viewer_1_0/dockwidget.cpp \
    ../src/3D_Viewer_1_0/main.cpp \
    ../src/3D_Viewer_1_0/mainwindow.cpp \
    ../src/3D_Viewer_1_0/opengl.cpp \
    ../src/parse.c \
    ../src/transformations.c \
    ../src/3D_Viewer_1_0/settings.cpp

HEADERS += \
    ../src/3D_Viewer_1_0/Figure.h \
    ../src/3D_Viewer_1_0/Line.h \
    ../src/3D_Viewer_1_0/dockwidget.h \
    ../src/3D_Viewer_1_0/mainwindow.h \
    ../src/3D_Viewer_1_0/opengl.h \
    ../src/3D_Viewer_1_0/qt_lib_includes.h \
    ../src/parse.h \
    ../src/transformations.h \
    ../src/3D_Viewer_1_0/settings.h

FORMS += \
    ../src/3D_Viewer_1_0/dockwidget.ui \
    ../src/3D_Viewer_1_0/mainwindow.ui \
    ../src/3D_Viewer_1_0/opengl.ui \
    ../src/3D_Viewer_1_0/settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

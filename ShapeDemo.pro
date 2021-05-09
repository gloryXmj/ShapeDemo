QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+= $$PWD/ \
              $$PWD/Figure/ \
              $$PWD/Algorithm/


DEPENDPATH+= $$PWD/ \
             $$PWD/Figure/ \
             $$PWD/Algorithm/

SOURCES += \
        Algorithm/cutpolygon.cpp \
        Color.cpp \
        Figure/Line.cpp \
        Figure/Point.cpp \
        Figure/Edge.cpp \
        Figure/Polygon.cpp \
        Figure/Rect.cpp \
        Figure/edges.cpp \
        Algorithm/FillControl.cpp \
        Algorithm/cutline.cpp \
        main.cpp \
        pixshape.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Algorithm/cutpolygon.h \
    Color.h \
    Figure/Line.h \
    Figure/Point.h \
    Figure/Edge.h \
    Figure/Polygon.h \
    Figure/Rect.h \
    Figure/edges.h \
    Algorithm/FillControl.h \
    Algorithm/PixControl.hpp \
    Algorithm/cutline.h \
    pixshape.h

LIBS += -luser32 \
        -lGdi32

# 计算机光栅图形学算法  Raster graphics

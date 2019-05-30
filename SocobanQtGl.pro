#-------------------------------------------------
#
# Project created by QtCreator 2019-04-09T13:59:46
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocobanQtGl
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
    movercountdecorator.cpp \
    socoban.cpp \
    appsettings.cpp \
    drawer.cpp \
    level.cpp \
    mainmenu.cpp \
    gamestate.cpp \
    point.cpp \
    map.cpp \
    selectlevelmenu.cpp \
    mover.cpp

HEADERS += \
    movercountdecorator.hpp \
    socoban.hpp \
    appsettings.hpp \
    drawer.hpp \
    level.hpp \
    mainmenu.hpp \
    gamestate.hpp \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml_iterators.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_utils.hpp \
    point.hpp \
    map.hpp \
    selectlevelmenu.hpp \
    mover.hpp

win32{
    LIBS += -lOpengl32
}
unix {
    LIBS += -lGL
}
FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

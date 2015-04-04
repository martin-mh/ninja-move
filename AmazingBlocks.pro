TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wall.cpp \
    player.cpp \
    game.cpp \
    utils.cpp

LIBS += -L"/home/imote/Development/SFML-build/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "/home/imote/Development/SFML/include"
DEPENDPATH += "/home/imote/Development/SFML/include"

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    wall.h \
    player.h \
    game.h \
    utils.hpp

CONFIG += c++11

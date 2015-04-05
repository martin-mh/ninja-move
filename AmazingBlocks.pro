TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wall.cpp \
    player.cpp \
    game.cpp \
    utils.cpp

LIBS += -L"C:\Users\Martin\Documents\SFML-2.2\lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "C:\Users\Martin\Documents\SFML-2.2\include"
DEPENDPATH += "C:\Users\Martin\Documents\SFML-2.2\include"

HEADERS += \
    wall.h \
    player.h \
    game.h \
    utils.hpp

CONFIG += c++11

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += \
    src/Game.cpp \
    src/Music.cpp \
    src/Sprite.cpp \
    src/State.cpp \
    src/Main.cpp \
    src/Rect.cpp \
    src/Vec2.cpp \
    src/Component.cpp \
    src/Gameobject.cpp \
    src/Sound.cpp \
    src/Face.cpp \
    src/TileSet.cpp \
    src/TileMap.cpp \
    src/Resources.cpp \
    src/InputManager.cpp \
    src/Camera.cpp \
    src/CameraFollower.cpp \
    src/Alien.cpp \
    src/Minion.cpp \
    src/Bullet.cpp \
    src/PenguinBody.cpp \
    src/PenguinCannon.cpp \
    src/Collider.cpp \
    src/Timer.cpp

LIBPATH += C:\SDL2-2.0.9\lib
LIBS += -lMinGW32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

INCLUDEPATH += C:\SDL2-2.0.9\include

HEADERS += \
    include/Game.h \
    include/Music.h \
    include/Sprite.h \
    include/State.h \
    include/SDL_include.h \
    include/Rect.h \
    include/Vec2.h \
    include/Component.h \
    include/Gameobject.h \
    include/Sound.h \
    include/Face.h \
    include/TileSet.h \
    include/TileMap.h \
    include/Resources.h \
    include/InputManager.h \
    include/Camera.h \
    include/CameraFollower.h \
    include/Alien.h \
    include/Minion.h \
    include/Bullet.h \
    include/PenguinBody.h \
    include/PenguinCannon.h \
    include/Collider.h \
    include/Collision.h \
    include/Timer.h

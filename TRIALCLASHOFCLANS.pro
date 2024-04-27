QT       += core gui\
          multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    building.cpp \
    enemy.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    maps.cpp \
    node.cpp \
    pathfinder.cpp \
    settings.cpp \
    tiles.cpp

HEADERS += \
    building.h \
    enemy.h \
    mainwindow.h \
    map.h \
    maps.h \
    node.h \
    pathfinder.h \
    settings.h \
    tiles.h

FORMS += \
    mainwindow.ui \
    maps.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MainWindow.qrc \
    Map1.qrc \
    Map2.qrc \
    Map3.qrc \
    Sounds.qrc \
    assets/delete.qrc \
    res.qrc \
    textfiles.qrc

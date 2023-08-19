QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# target
DESTDIR = bin

# include and library directory
INCLUDEPATH += include
LIBS += -Llib

# intermediate directory
CONFIG(debug, debug|release) {
    MOC_DIR = obj/debug/moc
    OBJECTS_DIR = obj/debug
    RCC_DIR = obj/debug/rcc
    UI_DIR = obj/debug/ui
} else {
    MOC_DIR = obj/release/moc
    OBJECTS_DIR = obj/release
    RCC_DIR = obj/release/rcc
    UI_DIR = obj/release/ui
}

# windows configure
win32 {
    CONFIG += embed_manifest_dll
    LIBS += -luuid -lole32
}

SOURCES += \
    audio.cpp \
    block/blockO.cpp \
    block/board.cpp \
    database/history.cpp \
    database/logindialog.cpp \
    database/registerdialog.cpp \
    database/users.cpp \
    formGame.cpp \
    formHelp.cpp \
    formHistory.cpp \
    formSetting.cpp \
    formStart.cpp \
    block/block.cpp \
    block/blockI.cpp \
    block/blockL.cpp \
    block/blockT.cpp \
    block/blockZ.cpp \
    block/object.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    audio.h \
    block/blockO.h \
    block/board.h \
    database/history.h \
    database/logindialog.h \
    database/registerdialog.h \
    database/users.h \
    formGame.h \
    formHelp.h \
    formHistory.h \
    formSetting.h \
    formStart.h \
    block/block.h \
    block/blockI.h \
    block/blockL.h \
    block/blockT.h \
    block/blockZ.h \
    block/object.h \
    mainwindow.h

FORMS += \
    database/logindialog.ui \
    database/registerdialog.ui \
    formGame.ui \
    formHelp.ui \
    formHistory.ui \
    formSetting.ui \
    formStart.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

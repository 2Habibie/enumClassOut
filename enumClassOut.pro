QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include
SOURCES += \
    src/main.cpp \
    src/dialog.cpp

HEADERS += \
    include/definition.h \
    include/dialog.h

FORMS += \
    src/dialog.ui

TRANSLATIONS += \
    resources/languages/EnumClassOut_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
include(gitversion.pri)

RESOURCES += \
    resources/resources.qrc

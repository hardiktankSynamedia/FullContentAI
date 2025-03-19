TEMPLATE = app

QT += quick qml widgets network

SOURCES += main.cpp \
    customtextpainter.cpp \
    imageloader.cpp \
    imagedisplay.cpp \
    contentview.cpp \
    menuasset.cpp \
    progressbar.cpp \
    border.cpp \
    gridview.cpp \
    performancelogger.cpp \
    blackscreenview.cpp \
    performancedatautil.cpp

HEADERS += \
    customtextpainter.h \
    imageloader.h \
    imagedisplay.h \
    contentview.h \
    menuasset.h \
    progressbar.h \
    border.h \
    gridview.h \
    performancelogger.h \
    blackscreenview.h \
    performancedatautil.h

RESOURCES += \
    qml.qrc \
    resources.qrc

DISTFILES += \
    main.qml \
    CustomTextNode.qml \
    CustomTextPainter.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

# Add OpenGL support
QT += opengl

# Add C++11 support
CONFIG += c++11

# Add private headers
QT += quick-private gui-private core-private

# For Qt 5.4.2 specifically
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtQuick/5.4.2
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtQuick/5.4.2/QtQuick
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtGui/5.4.2
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore/5.4.2

# Minimum required version
QT += core widgets quick gui opengl network quickwidgets

# Project name and version
TARGET = PyGraphCode
VERSION = 0.1.0

# C++ version
CONFIG += c++17

# Hide the separate console window on Windows
win32:CONFIG(release, debug|release) {
    LIBS -= -lconsole
    LIBS -= -luser32
    LIBS -= -lkernel32
}

# Path to the Emscripten SDK directory
#EMSDK_DIR = 3rdParty/emsdk

# Include the Emscripten toolchain file
#include($$EMSDK_DIR/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)

# Emscripten compiler paths
#QMAKE_CXX = $$EMSDK_DIR/upstream/emscripten/em++
#QMAKE_CXXFLAGS += -s USE_WEBGL2=1

# For IDE IntelliSense support
QMAKE_EXPORT_COMPILE_COMMANDS = 1

# iOS minimum version
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

# Add resource files
RESOURCES += \
    $$PWD/src/resources.qrc

# Header files
HEADERS += \
    $$PWD/src/MainWindow.h \
    $$PWD/src/MainWindowUI.h \
    $$PWD/src/AbstractElement.h \
    $$PWD/src/ConditionalElement.h \
    $$PWD/src/ForLoopElement.h \
    $$PWD/src/IfLoopElement.h \
    $$PWD/src/WriteVariableElement.h \
    $$PWD/src/ElementManager.h \
    $$PWD/src/ElementDragEventHandler.h \
    $$PWD/src/BuilderContainer.h \
    $$PWD/src/ContainerInformation.h \
    $$PWD/src/PlaceHolder.h \
    $$PWD/src/OperationElement.h \
    $$PWD/src/ResultedTextView.h \
    $$PWD/src/CodeText.h \
    $$PWD/src/ElementsCreator.h \
    $$PWD/src/BasicElementType.h \
    $$PWD/src/ReadVariableElement.h \
    $$PWD/src/ConstantDecimalElement.h \
    $$PWD/src/ConstantTextElement.h \
    $$PWD/src/InternalDragEventHandler.h \
    $$PWD/src/BuilderControlsButtons.h \
    $$PWD/src/ElementUserInputs.h \
    $$PWD/src/JSONDataHandler.h \
    $$PWD/src/ElementsListWidget.h \
    $$PWD/src/UserDefinedElement.h \
    $$PWD/src/CustomElementInputDialog.h

# Source files
SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/MainWindow.cpp \
    $$PWD/src/MainWindowUI.cpp \
    $$PWD/src/AbstractElement.cpp \
    $$PWD/src/ConditionalElement.cpp \
    $$PWD/src/ForLoopElement.cpp \
    $$PWD/src/IfLoopElement.cpp \
    $$PWD/src/WriteVariableElement.cpp \
    $$PWD/src/ElementManager.cpp \
    $$PWD/src/ElementDragEventHandler.cpp \
    $$PWD/src/BuilderContainer.cpp \
    $$PWD/src/PlaceHolder.cpp \
    $$PWD/src/OperationElement.cpp \
    $$PWD/src/ResultedTextView.cpp \
    $$PWD/src/CodeText.cpp \
    $$PWD/src/ElementsCreator.cpp \
    $$PWD/src/ReadVariableElement.cpp \
    $$PWD/src/ConstantDecimalElement.cpp \
    $$PWD/src/ConstantTextElement.cpp \
    $$PWD/src/InternalDragEventHandler.cpp \
    $$PWD/src/BuilderControlsButtons.cpp \
    $$PWD/src/ElementUserInputs.cpp \
    $$PWD/src/JSONDataHandler.cpp \
    $$PWD/src/ElementsListWidget.cpp \
    $$PWD/src/UserDefinedElement.cpp \
    $$PWD/src/CustomElementInputDialog.cpp

# Enable necessary Qt modules
QT += core gui widgets quick quickwidgets

# Set the output directory for the HTML file
CONFIG(release, debug|release) {
    target.path = $$OUT_PWD/release
    target.files = $$TARGET.html
    INSTALLS += target
}

# Additional configurations for the debug mode
CONFIG(debug, debug|release) {
    LIBS -= -lconsole
    LIBS -= -luser32
    LIBS -= -lkernel32
}

# Add additional libraries if needed
# LIBS += ...

# Add additional include paths if needed
# INCLUDEPATH += ...

# Add additional defines if needed
# DEFINES += ...

# Add additional compiler flags if needed
# QMAKE_CXXFLAGS += ...

# Add additional linker flags if needed
# QMAKE_LFLAGS += ...

# Define the project name and version
TEMPLATE = app
TARGET = PyGraphCode
VERSION = 0.1.0

# Define the target platform and architecture
QMAKE_TARGET.arch = wasm

# Set the C++ version and compiler flags
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# Enable precompiled headers
#PRECOMPILED_HEADER = $$PWD/src/pch.h

# Define the source files
SOURCES += $$PWD/src/main.cpp \
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

# Define the header files
HEADERS += $$PWD/src/MainWindow.h \
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

# Define the resource files
RESOURCES += $$PWD/src/resources.qrc

# Include the required Qt modules
QT += core gui widgets

# WebAssembly-specific settings
wasm {
    # Set the output directory for WebAssembly build
    DESTDIR = $$PWD/build-wasm

    # Enable WebAssembly support
    CONFIG += wasm

    # Include the Emscripten libraries
    INCLUDEPATH += $$PWD/3rdParty/emsdk/upstream/emscripten/system/include
    LIBS += -L $$PWD/emsdk/upstream/emscripten/system/lib \
            -lglut -lGLU -lGL

    # Set the deployment directory for WebAssembly build
    QMAKE_PREFIX_PATH += $$PWD/build-wasm/qtbase

    # Link against the Emscripten libraries
    LIBS += -s USE_GLFW=3 -s WASM=1 -s USE_WEBGL2=1 -s PTHREAD_POOL_SIZE=100

    # Add WebAssembly-specific compiler flags
    QMAKE_CXXFLAGS += -s FORCE_FILESYSTEM=1

    QMAKE_LFLAGS += -s ASYNCIFY -Os
}

# Link against the Qt libraries
LIBS += -L "C:/Qt6/6.5.1/wasm_multithread/lib/libQt6Core.a" -L "C:/Qt6/6.5.1/wasm_multithread/lib/libQt6Gui.a" -L "C:/Qt6/6.5.1/wasm_multithread/lib/libQt6Widgets.a"

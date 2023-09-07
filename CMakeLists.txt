cmake_minimum_required(VERSION 3.10)
project(PyGraph LANGUAGES CXX VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Hide the seprate console window.
if(WIN32)
    #set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# For IDE intellisense support
set(CMAKE_EXPORT_COMPILE_COMMANDS)

# set the IOS minimum version 10.14
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
#enable_testing()

# Add resource files
set(RESOURCES 
   ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.qrc
   ${CMAKE_CURRENT_SOURCE_DIR}/src/stylesheet.css
)


set(HEADERS	
      ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowUI.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/AbstractElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConditionalElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ForLoopElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/IfLoopElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/WriteVariableElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementManager.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementDragEventHandler.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BuilderContainer.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ContainerInformation.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/OperationElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ResultedTextView.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/CodeText.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsCreator.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BasicElementType.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ReadVariableElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantDecimalElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantTextElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/InternalDragEventHandler.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BuilderControlsButtons.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementUserInputs.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/JSONDataHandler.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsListWidget.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/UserDefinedElement.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomElementInputDialog.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ParameterUIBuilder.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/InputLabelDialog.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/SettingsManager.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BuilderControlPanel.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ImageButton.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/DeleteItem.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsControlButtons.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsLeftNavigator.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/SearchBarWidget.h
   )

set(SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowUI.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/AbstractElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConditionalElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ForLoopElement.cpp	
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/IfLoopElement.cpp	
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/WriteVariableElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementManager.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementDragEventHandler.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BuilderContainer.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/OperationElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ResultedTextView.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/CodeText.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsCreator.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ReadVariableElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantDecimalElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantTextElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/InternalDragEventHandler.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BuilderControlsButtons.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementUserInputs.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/JSONDataHandler.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsListWidget.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/UserDefinedElement.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomElementInputDialog.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ParameterUIBuilder.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/InputLabelDialog.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/SettingsManager.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BuilderControlPanel.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ImageButton.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/DeleteItem.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsControlButtons.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementsLeftNavigator.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/SearchBarWidget.cpp
    )



add_subdirectory(src)
add_subdirectory(test)


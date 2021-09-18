cmake_minimum_required(VERSION 3.15)

project(qttest CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "..." FORCE)
endif()

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	set(QT_INCLUDE "/usr/include/x86_64-linux-gnu/qt5")
endif()

if(WIN32)
	# On Windows, the install dir must be specified, as it's not standardized
	if(DEFINED QT_BASEDIR)
		# Add it to the prefix path so find_package can find it
		list(APPEND CMAKE_PREFIX_PATH ${QT_BASEDIR})
		set(QT_INCLUDE ${QT_BASEDIR}/include)
		# CMake has an odd policy that links a special link lib for Qt on newer versions of CMake. Enable it so we don't get spammed, and I get to write less
		cmake_policy(SET CMP0020 NEW)
	else()
		message(FATAL_ERROR "--!@ Please define your QT install dir with -DQT_BASEDIR=C:/your/qt5/here")
	endif()
endif()	

message("Using ${QT_INCLUDE} as our Qt include dir")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC
	# Dialogs
	dialogs/Options.h
	dialogs/Options.cpp
	dialogs/GoTo.cpp
	dialogs/GoTo.h 
	dialogs/RunMapNormal.h
	dialogs/RunMapNormal.cpp
	dialogs/MapInformation.h
	dialogs/MapInformation.cpp
	
	# Widgets 
	widgets/FileSelector.h
	widgets/FileSelector.cpp
	widgets/PrefSlider.h
	widgets/PrefSlider.cpp
	
	# Everything else
	qttest.cpp
	Zoo.h
	Zoo.cpp)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
	
add_executable(qttest ${SRC})
target_link_libraries(qttest PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
target_include_directories(qttest PRIVATE ${QT_INCLUDE} ${QT_INCLUDE}/QtWidgets ${QT_INCLUDE}/QtGui ${QT_INCLUDE}/QtCore)


if(WIN32)
	# Set up the debugger so it can run the program without copying a million dlls
	set_target_properties(qttest PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${QT_BASEDIR}/bin;")
endif()
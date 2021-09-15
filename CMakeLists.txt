project(qttest CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SRC
	qttest.cpp
	Preferences.h
	Preferences.cpp
	FileSelector.h
	FileSelector.cpp
	PrefSlider.h
	PrefSlider.cpp)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
	
add_executable(qttest ${SRC})
target_link_libraries(qttest PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
target_include_directories(qttest PRIVATE /usr/include/x86_64-linux-gnu/qt5/ /usr/include/x86_64-linux-gnu/qt5/QtWidgets /usr/include/x86_64-linux-gnu/qt5/QtGui /usr/include/x86_64-linux-gnu/qt5/QtCore)

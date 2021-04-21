cmake_minimum_required(VERSION 3.16)

project(project_SignalsAndSlots)

# The CMAKE_AUTOMOC setting runs Meta-Object Compiler (MOC) automatically when required.
# By running the MOC on class definitions that contain Q_OBJECT macro, a C++ source file is generated which initializes the Meta-Object System (MOS).
# This generated source file is either #include'd into the class's source file or, more usually, compiled and linked with the class's implementation.
# In the absence of CMAKE_AUTOMOC, compiler errors along the lines of "undefined reference to vtable for ..." will be generated
# Note: when using qmake, the makefile rules to automatically invoke MOC will be added to project's makefile.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Not sure if it is needed
set(CMAKE_AUTOUIC ON) # Not sure if it is needed

# Locate the libraries and header files shipped with Qt
# Each Qt module that is loaded defines a CMake library target.
find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(
"${PROJECT_NAME}"
main.cpp
ConverterC.h
ConverterC.cpp
ButtonC.h
ButtonC.cpp
)

# Pass the name of the library target to target_link_libraries to use the respective library.
# The target names start with Qt5::, followed by the module name.
# This command automatically adds the appropriate include directories, compile definitions, the position-independent-code flag etc
# and also links to the qtmain.lib library on Windows.
target_link_libraries("${PROJECT_NAME}" Qt5::Core Qt5::Widgets)

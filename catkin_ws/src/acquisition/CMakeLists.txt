# Required CMake version
cmake_minimum_required(VERSION 3.0.2)

# Name of the project
project(acquisition)

# Find the catkin build system, and any other packaes on which the build depends
find_package(catkin REQUIRED COMPONENTS roscpp)

# Declare the catkin package
catkin_package()

# Specify the location of header files
include_directories(inlcude ${catkin_INCLUDE_DIRS})

# Declare the executable, along with its source files. For multiple executables multiple copies of this line 
# are to be used.
add_executable(acquisition acquisition.cpp)

# Specify libraries aganist which to link. Again, this line is to be copied for each distinct executable in the package
target_link_libraries(acquisition ${catkin_LIBRARIES})

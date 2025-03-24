cmake_minimum_required(VERSION 3.13)  # CMake version check
project(demo_project)


# Setup variable
set(EXE_NAME ${PROJECT_NAME}) # setup the executable output name
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output all the executable to ./bin directory

# Setup compile files
include_directories(include/) #Add include files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.cpp)# Add source files automatically

# Define the source files explicitly
# set(SOURCE_FILES  # Add source files
#     src/main.cpp
# )

# Building process
add_executable(${EXE_NAME} ${SOURCE_FILES}) # Make executable

# Post build command
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_command( # Post build command
    TARGET ${EXE_NAME} 
    POST_BUILD 
    COMMAND cp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}-unstrip
    COMMAND ${CMAKE_STRIP} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
)
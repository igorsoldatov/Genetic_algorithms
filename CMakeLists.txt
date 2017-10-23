cmake_minimum_required(VERSION 3.8)
project(Evolution_live_organisms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp bio.cpp bio.h Predator.cpp Predator.h config.h Game.cpp Game.h)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#find_package(FREEGLUT REQUIRED)
find_package(GLUT REQUIRED)

if (NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif ()

include_directories(
        ${PROJECT_SOURCE_DIR}
        #${FREEGLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        #${FREEGLUT_LIBRARY}
        ${GLEW_LIBRARY}
        ${GLUT_LIBRARY}
)

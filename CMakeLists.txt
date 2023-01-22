cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_EXTENSIONS OFF)
set(PROJECT_NAME GL_2D_TEST)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

file(GLOB_RECURSE
	SOURCES CONFIGURE_DEPENDS
	"./src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
	${PROJECT_NAME} PRIVATE
	"./include/")

target_link_libraries(
	${PROJECT_NAME} PRIVATE
	"glew32"
	"glfw3"
	"opengl32")

target_compile_definitions(
	${PROJECT_NAME} PRIVATE
	GLFW_INCLUDE_NONE)

target_compile_options(
	${PROJECT_NAME} PRIVATE
	-Wall -Wextra -pedantic)

target_compile_features(
	${PROJECT_NAME} PRIVATE
	cxx_std_17)

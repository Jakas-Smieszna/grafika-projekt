# CMakeList.txt : CMake project for GrafikaProjekt, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project (
  GrafikaProjekt
  VERSION 1.0
  LANGUAGES CXX C
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

message(STATUS "Cmake module path is ${CMAKE_MODULE_PATH}.")
find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OPENGL_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(GLM REQUIRED)
message(STATUS "Found GLM in ${GLM_INCLUDE_DIR}")

set(GLAD_INCLUDE_PATH "./include" PATH "The directory that contains GL/glfw.h" )

include(FetchContent)
FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG c35200e38ea8f058812b83de2ef32c6093b0ece2 # wersja 5.4.3
)
# set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

# Add source to this project's executable.
include_directories(
	${GLFW_INCLUDE_PATH}
	${GLAD_INCLUDE_PATH}
  ${GLM_INCLUDE_DIR}
  _deps/assimp-src/include # asset import library
  _deps/assimp-build/include # asset import library build stuff
)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Kod źródłowy projektu itp.
add_subdirectory(src)

# TODO: Add tests and install targets if needed.

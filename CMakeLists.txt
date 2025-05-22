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

# Add source to this project's executable.

include_directories(
	${GLFW_INCLUDE_PATH}
	${GLAD_INCLUDE_PATH}
  ${GLM_INCLUDE_DIR}
)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Kod źródłowy projektu itp.
add_subdirectory(src)

# TODO: Add tests and install targets if needed.

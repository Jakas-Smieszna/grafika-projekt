# CMakeList.txt : CMake project for GrafikaProjekt, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8...4.0)

project (
  GrafikaProjekt
  VERSION 1.0
  LANGUAGES CXX C
)
find_package(OpenGL REQUIRED)

set(GLFW_INCLUDE_PATH "./include" PATH "The directory that contains GL/glfw.h" )
set(GLFW_LIBRARY "./lib/lib-vc2022/glfw3.lib" PATH)

set(GLAD_INCLUDE_PATH "./include" PATH "The directory that contains GL/glfw.h" )
#set(GLAD_LIBRARY "" CACHE FILEPATH "libglfw.a or glfw.lib" )

set(SOURCE_FILES
  # Dodawajcie tu pliki źródłowe.
  src/shader.h
  src/VBO.h
  src/VAO.h
  src/EBO.h
  src/main.cpp
  src/shader.cpp
  src/VAO.cpp
  src/VBO.cpp
  src/EBO.cpp
  src/glad.c
  SRC/
)
message(STATUS "GLFW incl path:")
message(STATUS ${GLFW_INCLUDE_PATH})
# Add source to this project's executable.

include_directories(
  GLFW_INCLUDE_PATH
	${GLFW_INCLUDE_PATH}
	${GLAD_INCLUDE_PATH}
)

add_executable (GrafikaProjekt
  ${SOURCE_FILES}
)

target_link_libraries(GrafikaProjekt
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
	${GLFW_LIBRARY}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GrafikaProjekt PROPERTY CXX_STANDARD 20)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# TODO: Add tests and install targets if needed.

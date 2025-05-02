
# Pliki nagłówkowe.
# Tu nie trzeba niczego edytować.
file(GLOB HEADER_LIST CONFIGURE_DEPENDS 
    "${GrafikaProjekt_SOURCE_DIR}/src/*.h"
)
set(PROJ_FILES
# Pliki projektu
    main.cpp
    shader.cpp
    VAO.cpp
    VBO.cpp
    EBO.cpp
# Biblioteki
    glad.c
)

add_executable(GrafikaProjekt 
    ${PROJ_FILES}
    ${HEADER_LIST}
)

target_link_libraries(GrafikaProjekt PRIVATE
	${OPENGL_LIBRARY}
	${GLFW3_LIBRARY}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GrafikaProjekt PROPERTY CXX_STANDARD 20)
endif()

source_group(
    TREE "${PROJECT_SOURCE_DIR}/src"
    PREFIX "Pliki Nagłówkowe"
    FILES ${HEADER_LIST}
)


set(PROJ_FILES
# Pliki projektu
    main.cpp
    shader.cpp
    VAO.cpp
    VBO.cpp
    EBO.cpp
    Kamera.cpp
    Tekstury.cpp
# Biblioteki
    glad.c
)

add_executable(GrafikaProjekt ${PROJ_FILES} )

target_link_libraries(GrafikaProjekt PRIVATE
	${OPENGL_LIBRARY} ${GLFW3_LIBRARY}
)

set_property(TARGET GrafikaProjekt PROPERTY CXX_STANDARD 20)
if(UNIX)
    set(CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}/bin")
    set_property(TARGET GrafikaProjekt PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
endif(UNIX)
file(COPY "./shaders" DESTINATION "${CMAKE_BINARY_DIR}")
message(STATUS "Shaders have been copied to ${CMAKE_BINARY_DIR}")
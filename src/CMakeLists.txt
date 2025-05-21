

set(PROJ_FILES
# Pliki projektu
    main.cpp
    shader.cpp
    VAO.cpp
    VBO.cpp
    EBO.cpp
    Kamera.cpp
    Tekstury.cpp
    mesh.cpp
    model.cpp
# Biblioteki
    stb.cpp
    glad.c
)

add_executable(GrafikaProjekt ${PROJ_FILES} )

target_link_libraries(GrafikaProjekt PRIVATE
	${OPENGL_LIBRARY} ${GLFW3_LIBRARY} ${assimp_LIBRARIES}
)

target_compile_definitions(GrafikaProjekt PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD>
)

set_target_properties(GrafikaProjekt PROPERTIES
    CXX_STANDARD 20
)

if(UNIX)
    set(DIR_TO_COPY_RESOURCES "${CMAKE_BINARY_DIR}/bin")
    set_property(TARGET GrafikaProjekt PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
elseif(WIN32)
    set(DIR_TO_COPY_RESOURCES "${CMAKE_BINARY_DIR}/src")
endif(UNIX)
file(COPY "./shaders" DESTINATION "${DIR_TO_COPY_RESOURCES}")
file(COPY "./resources" DESTINATION "${DIR_TO_COPY_RESOURCES}")
message(STATUS "Shaders and resources have been copied to ${DIR_TO_COPY_RESOURCES}")

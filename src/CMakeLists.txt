

set(PROJ_FILES
# Pliki projektu
    main.cpp
    shader.cpp
    VAO.cpp
    VBO.cpp
    EBO.cpp
    Kamera.cpp
    Tekstury.cpp
    stb.cpp
# Biblioteki
    glad.c
)

add_executable(GrafikaProjekt ${PROJ_FILES} )

target_link_libraries(GrafikaProjekt PRIVATE
	${OPENGL_LIBRARY} ${GLFW3_LIBRARY}
)

set_property(TARGET GrafikaProjekt PROPERTY CXX_STANDARD 20)
if(UNIX)
    set(DIR_TO_COPY_RESOURCES "${CMAKE_BINARY_DIR}/bin")
    set_property(TARGET GrafikaProjekt PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
elseif(WIN32)
    set(DIR_TO_COPY_RESOURCES "${CMAKE_BINARY_DIR}/src")
endif(UNIX)

file(MAKE_DIRECTORY ${DIR_TO_COPY_RESOURCES})
ADD_CUSTOM_TARGET(link_target ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/src/resources" "${DIR_TO_COPY_RESOURCES}/resources" 
                  COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/src/shaders" "${DIR_TO_COPY_RESOURCES}/shaders" )
# file(COPY "./shaders" DESTINATION "${DIR_TO_COPY_RESOURCES}")
# file(COPY "./resources" DESTINATION "${DIR_TO_COPY_RESOURCES}")
# message(STATUS "Shaders and resources have been copied to ${DIR_TO_COPY_RESOURCES}")

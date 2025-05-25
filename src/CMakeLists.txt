

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
    #model.cpp
    terrainGenerator.cpp
# Biblioteki
    stb.cpp
    Zegary.cpp
    StatusGry.cpp
# Biblioteki Kici kici kici kici kici kici kici kici kici kici
    glad.c
 "helper/tsqueue.cpp")

add_executable(GrafikaProjekt ${PROJ_FILES} )

target_link_libraries(GrafikaProjekt PRIVATE
	${OPENGL_LIBRARY} ${GLFW3_LIBRARY} 
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

file(MAKE_DIRECTORY ${DIR_TO_COPY_RESOURCES})

#ADD_CUSTOM_TARGET(link_target ALL
#                  COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/src/resources" "${DIR_TO_COPY_RESOURCES}/resources" 
#                  COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/src/shaders" "${DIR_TO_COPY_RESOURCES}/shaders" )
#ADD_CUSTOM_TARGET(copy_resource_files ALL
#    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different  "${CMAKE_SOURCE_DIR}/src/resources" "${DIR_TO_COPY_RESOURCES}/resources" 
#    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different  "${CMAKE_SOURCE_DIR}/src/shaders" "${DIR_TO_COPY_RESOURCES}/shaders" 
)

add_dependencies(GrafikaProjekt copy_resource_files)
# file(COPY "./shaders" DESTINATION "${DIR_TO_COPY_RESOURCES}")
# file(COPY "./resources" DESTINATION "${DIR_TO_COPY_RESOURCES}")
# message(STATUS "Shaders and resources have been copied to ${DIR_TO_COPY_RESOURCES}")

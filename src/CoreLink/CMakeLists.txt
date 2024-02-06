add_executable( CoreLink
                main.cpp
                CoreManager.cpp
        )

target_include_directories(
        CoreLink PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${glad_BINARY_DIR}/include
        ${glfw_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${imgui_SOURCE_DIR}/misc/cpp
        ${glm_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src/Common
)

target_link_directories(
        CoreLink PRIVATE
)

target_link_libraries(
    CoreLink PRIVATE
    imgui
    glad
    glfw
    glm
    yaml-cpp
    ${OPENGL_LIBRARY}
)        

include_directories(
        ${PROJECT_SOURCE_DIR}/src/Common
        ${CMAKE_CURRENT_SOURCE_DIR})

ADD_LIBRARY( chip8-emu SHARED
        interface.cpp
        chip8.cpp
        memoryc8/memoryc8.cpp
        cpu/cpu.cpp
        cpu/opcodes.cpp
)

target_link_libraries(
    chip8-emu PRIVATE
    yaml-cpp
)        

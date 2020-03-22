file(GLOB BASE_SRC "*.c" "*.cpp" "../ext/imgui/*.cpp" "../ext/glad/src/glad.c")
file(GLOB BASE_HEADERS "*.hpp" ".h")

if(WIN32)
    add_library(nautilus STATIC ${BASE_SRC})
    target_link_libraries(nautilus ${Vulkan_LIBRARY} ${GLFW3_LIBRARY} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES} ${WINLIBS})
else(WIN32)
    add_library(nautilus STATIC ${BASE_SRC})
    target_link_libraries(nautilus stdc++fs dl ${Vulkan_LIBRARY} ${GLFW3_LIBRARY} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES} ${XCB_LIBRARIES} ${WAYLAND_CLIENT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif(WIN32)

add_custom_command(TARGET nautilus PRE_BUILD COMMAND cp -r ${BASE_HEADERS} -t ${NAUTILUS_HEADER_MOVE_DIR})
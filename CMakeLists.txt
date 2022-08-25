#Sets minimum cmake version 
cmake_minimum_required(VERSION 3.14)

#Sets project name to CS1950UEngine
project(CS1950UEngine)

#Tells compiler to use c++ 20
set(CMAKE_CXX_STANDARD 20)
#Makes c++ 20 required
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Setting path macros
set(GLFW_SOURCE_DIR "external/glfw-3.3.8")
set(GLEW_SOURCE_DIR "external/glew")
set(GLM_SOURCE_DIR "external/glm-master")
set(STB_SOURCE_DIR "external/stb")

#GLFW settings
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

add_subdirectory(${GLFW_SOURCE_DIR})
add_subdirectory(${GLM_SOURCE_DIR})

include_directories(${GLFW_SOURCE_DIR}/include
                    ${GLFW_SOURCE_DIR}/deps
                    ${GLEW_SOURCE_DIR}/include
                    ${STB_SOURCE_DIR}
                    Graphics
                    )

add_library(glew STATIC ${GLEW_SOURCE_DIR}/src/glew.c)

add_executable(${PROJECT_NAME}
    window.h
    core.h
    Graphics/graphics.h
    Graphics/global.h
    Graphics/debug.h
    Graphics/vbo.h
    Graphics/vao.h
    Graphics/camera.h
    Graphics/shaderloader.h
    Graphics/shader.h
    Graphics/texture.h
    Graphics/renderbuffer.h

    main.cpp
    window.cpp
    core.cpp
    Graphics/graphics.cpp
    Graphics/vbo.cpp
    Graphics/vao.cpp
    Graphics/camera.cpp
    Graphics/shader.cpp
    Graphics/texture.cpp
    Graphics/renderbuffer.cpp

    Resources/Shaders/default.frag
    Resources/Shaders/default.vert
)

find_package(OpenGL REQUIRED)


target_link_libraries(${PROJECT_NAME} glfw glew glm)


if (WIN32)
  add_compile_definitions(GLEW_STATIC)
  target_link_libraries(${PROJECT_NAME}
      opengl32
      glu32
  )
endif()

if (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME}
      GLU
  )
endif()

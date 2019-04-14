# Projects Settings
cmake_minimum_required (VERSION 3.1)
project(smk)

add_library(smk
  src/Color.cpp
  src/Drawable.cpp
  src/Font.cpp
  src/GL_CHECK_ERROR.cpp
  src/Input.cpp
  src/Screen.cpp
  src/Shader.cpp
  src/Shape.cpp
  src/Sound.cpp
  src/Sprite.cpp
  src/StbImage.cpp
  src/StbImage.hpp
  src/Text.cpp
  src/Texture.cpp
  src/View.cpp
)

target_include_directories(smk
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    src
)

set_property(TARGET smk PROPERTY CXX_STANDARD 14)
add_definitions(-DGLM_FORCE_RADIANS)

# Detect emscripten is used.
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
  target_link_libraries(smk PUBLIC "-s USE_GLFW=3")
  target_link_libraries(smk PUBLIC "-s USE_WEBGL2=1")
else()
  target_link_libraries(smk PUBLIC glfw)
  target_link_libraries(smk PUBLIC libglew_static)
endif()

target_link_libraries(smk PUBLIC glm)
target_link_libraries(smk PRIVATE freetype)
target_link_libraries(smk PRIVATE OpenAL)

# Projects Settings
cmake_minimum_required (VERSION 3.1)
project(smk)

add_library(smk
  include/smk/Audio.hpp
  include/smk/Color.hpp
  include/smk/Drawable.hpp
  include/smk/Font.hpp
  include/smk/GL_CHECK_ERROR.hpp
  include/smk/Input.hpp
  include/smk/OpenGL.hpp
  include/smk/Screen.hpp
  include/smk/Shader.hpp
  include/smk/Shape.hpp
  include/smk/Sound.hpp
  include/smk/SoundBuffer.hpp
  include/smk/Sprite.hpp
  include/smk/Text.hpp
  include/smk/Texture.hpp
  include/smk/BlendMode.hpp
  include/smk/RenderState.hpp
  include/smk/Vertex.hpp
  include/smk/VertexArray.hpp
  include/smk/View.hpp
  src/smk/Audio.cpp
  src/smk/BlendMode.cpp
  src/smk/Color.cpp
  src/smk/Drawable.cpp
  src/smk/Font.cpp
  src/smk/GL_CHECK_ERROR.cpp
  src/smk/Input.cpp
  src/smk/RenderState.cpp
  src/smk/Screen.cpp
  src/smk/Shader.cpp
  src/smk/Shape.cpp
  src/smk/Sound.cpp
  src/smk/SoundBuffer.cpp
  src/smk/Sprite.cpp
  src/smk/StbImage.cpp
  src/smk/StbImage.hpp
  src/smk/Text.cpp
  src/smk/Texture.cpp
  src/smk/VertexArray.cpp
  src/smk/View.cpp
)

target_include_directories(smk
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    src/
)

target_compile_options(main
 PRIVATE
  -Wall
  -Werror
  -pedantic-errors
  -Wextra
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
target_link_libraries(smk PRIVATE libnyquist)

get_property(includes
        TARGET libnyquist
        PROPERTY INCLUDE_DIRECTORIES
        )
foreach(a ${includes})
  message(STATUS ${a})
endforeach()

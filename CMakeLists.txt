# Projects Settings
cmake_minimum_required (VERSION 3.1)
project(opengl-cmake-skeleton-webassembly)

# The main executable
add_executable(main
  src/Application.cpp
  src/Application.cpp
  src/Input.cpp
  src/Input.h
  src/MyApplication.cpp
  src/MyApplication.cpp
  src/Shader.cpp
  src/Shader.hpp
  src/TextureManager.cpp
  src/TextureManager.hpp
  src/glError.cpp
  src/glError.hpp
  src/main.cpp
  src/resource.cpp
  src/resource.hpp
  src/opengl.hpp
  src/stb_image.cpp
  src/stb_image.h
)

set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# Detect emscripten is used.
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
  set_target_properties(main PROPERTIES OUTPUT_NAME "main.js")

  # glfw
  #string(APPEND CMAKE_CXX_FLAGS " -s USE_GLFW=3")

  string(APPEND CMAKE_CXX_FLAGS " -s DEMANGLE_SUPPORT=1")
  string(APPEND CMAKE_CXX_FLAGS " -s DISABLE_EXCEPTION_CATCHING=2")
  string(APPEND CMAKE_CXX_FLAGS " -s USE_GLFW=3")
  string(APPEND CMAKE_CXX_FLAGS " -s USE_WEBGL2=1")
  string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")

  # Release flags
  #string(APPEND CMAKE_CXX_FLAGS " --closure 1")
  #string(APPEND CMAKE_CXX_FLAGS " --js-opts 3")
  #string(APPEND CMAKE_CXX_FLAGS " --llvm-lto 3")
  #string(APPEND CMAKE_CXX_FLAGS " --llvm-opts 3")
  #string(APPEND CMAKE_CXX_FLAGS " -O3")

  # Copy the index.html file.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
  )

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/style.css
    ${CMAKE_CURRENT_BINARY_DIR}/style.css
  )

  # Allow some files to be fetched.
  file(GLOB shader_files "./shader/*")
  file(GLOB img_files "./img/*")
  foreach(file ${shader_files} ${img_files})
    file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${file})
    string(APPEND CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
    message(STATUS CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
  endforeach()
  
else() # Not Web
  # glfw
  add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
  target_link_libraries(main PRIVATE glfw)

  # glew
  add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
  target_link_libraries(main PRIVATE libglew_static)
endif()

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

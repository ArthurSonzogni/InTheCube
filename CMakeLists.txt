# Projects Settings
cmake_minimum_required (VERSION 3.1)
project(opengl-cmake-skeleton-webassembly)

# The main executable
add_executable(main
  src/Accelerator.cpp
  src/Accelerator.hpp
  src/Arrow.cpp
  src/Arrow.hpp
  src/ArrowLauncher.cpp
  src/ArrowLauncher.hpp
  src/ArrowLauncherDetector.cpp
  src/ArrowLauncherDetector.hpp
  src/BackgroundMusic.cpp
  src/BackgroundMusic.hpp
  src/Block.cpp
  src/Block.hpp
  src/Button.cpp
  src/Button.hpp
  src/Clock.hpp
  src/Cloner.cpp
  src/Cloner.hpp
  src/Collision.cpp
  src/Collision.hpp
  src/Creeper.cpp
  src/Creeper.hpp
  src/Decor.cpp
  src/Decor.hpp
  src/Detector.cpp
  src/Detector.hpp
  src/Electricity.cpp
  src/Electricity.hpp
  src/FallingBlock.cpp
  src/FallingBlock.hpp
  src/FinishBlock.cpp
  src/FinishBlock.hpp
  src/Forme.cpp
  src/Forme.hpp
  src/Glass.cpp
  src/Glass.hpp
  src/Hero.cpp
  src/Hero.hpp
  src/InvisibleBlock.cpp
  src/InvisibleBlock.hpp
  src/Lang.cpp
  src/Lang.hpp
  src/LaserTurret.cpp
  src/LaserTurret.hpp
  src/Level.cpp
  src/Level.hpp
  src/LevelListLoader.cpp
  src/LevelListLoader.hpp
  src/MovableBlock.cpp
  src/MovableBlock.hpp
  src/MovingBlock.cpp
  src/MovingBlock.hpp
  src/Particule.cpp
  src/Particule.hpp
  src/Pic.cpp
  src/Pic.hpp
  src/Pincette.cpp
  src/Pincette.hpp
  src/Resource.cpp
  src/Resource.hpp
  src/SaveManager.cpp
  src/SaveManager.hpp
  src/Special.cpp
  src/Special.hpp
  src/StaticMirror.cpp
  src/StaticMirror.hpp
  src/Teleporter.cpp
  src/Teleporter.hpp
  src/TextPopup.cpp
  src/TextPopup.hpp
  src/main.cpp
)

set_property(TARGET main PROPERTY CXX_STANDARD 14)
add_definitions(-DGLM_FORCE_RADIANS)

# Detect emscripten is used.
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
  set_target_properties(main PROPERTIES OUTPUT_NAME "main.js")

  string(APPEND CMAKE_CXX_FLAGS " -s DEMANGLE_SUPPORT=1")
  string(APPEND CMAKE_CXX_FLAGS " -s DISABLE_EXCEPTION_CATCHING=2")
  string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")
  string(APPEND CMAKE_CXX_FLAGS " -s ALLOW_MEMORY_GROWTH=1")

  # Release flags
  string(APPEND CMAKE_CXX_FLAGS " --closure 1")
  string(APPEND CMAKE_CXX_FLAGS " --js-opts 3")
  string(APPEND CMAKE_CXX_FLAGS " --llvm-lto 3")
  string(APPEND CMAKE_CXX_FLAGS " --llvm-opts 3")
  string(APPEND CMAKE_CXX_FLAGS " -O3")

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
  file(GLOB save_files "./sav/*")
  file(GLOB lvl_files "./lvl/*")
  file(GLOB lang_files "./lang/*")
  file(GLOB font_files "./font/*")
  foreach(file ${shader_files} ${img_files} ${save_files} ${lvl_files} ${lang_files} ${font_files})
    file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${file})
    string(APPEND CMAKE_CXX_FLAGS " --preload-file ${file}@/${relative_file}")
  endforeach()
else()
  add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
  add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
endif()

add_subdirectory(lib/freetype2 EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(src/smk EXCLUDE_FROM_ALL)

target_link_libraries(main PRIVATE smk)

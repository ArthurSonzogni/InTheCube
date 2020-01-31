# Projects Settings
cmake_minimum_required (VERSION 3.11)

set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

add_subdirectory(third_party)
project(InTheCube)

# The inthecube executable
add_executable(inthecube
  src/activity/Activity.hpp
  src/activity/WelcomeScreen.hpp
  src/activity/WelcomeScreen.cpp
  src/activity/IntroScreen.hpp
  src/activity/IntroScreen.cpp
  src/activity/MainScreen.hpp
  src/activity/MainScreen.cpp
  src/activity/LevelScreen.cpp
  src/activity/LevelScreen.hpp
  src/activity/ResourceLoadingScreen.cpp
  src/activity/ResourceLoadingScreen.hpp
  src/game/Accelerator.cpp
  src/game/Accelerator.hpp
  src/game/Arrow.cpp
  src/game/Arrow.hpp
  src/game/Laser.cpp
  src/game/Laser.hpp
  src/game/ArrowLauncher.cpp
  src/game/ArrowLauncher.hpp
  src/game/ArrowLauncherDetector.cpp
  src/game/ArrowLauncherDetector.hpp
  src/game/BackgroundMusic.cpp
  src/game/BackgroundMusic.hpp
  src/game/Block.cpp
  src/game/Block.hpp
  src/game/Button.cpp
  src/game/Button.hpp
  src/game/Cloner.cpp
  src/game/Cloner.hpp
  src/game/Collision.cpp
  src/game/Collision.hpp
  src/game/Creeper.cpp
  src/game/Creeper.hpp
  src/game/Decor.cpp
  src/game/Decor.hpp
  src/game/Detector.cpp
  src/game/Detector.hpp
  src/game/Electricity.cpp
  src/game/Electricity.hpp
  src/game/FallingBlock.cpp
  src/game/FallingBlock.hpp
  src/game/FinishBlock.cpp
  src/game/FinishBlock.hpp
  src/game/Forme.cpp
  src/game/Forme.hpp
  src/game/Glass.cpp
  src/game/Glass.hpp
  src/game/Hero.cpp
  src/game/Hero.hpp
  src/game/InvisibleBlock.cpp
  src/game/InvisibleBlock.hpp
  src/game/Lang.cpp
  src/game/Lang.hpp
  src/game/LaserTurret.cpp
  src/game/LaserTurret.hpp
  src/game/Level.cpp
  src/game/Level.hpp
  src/game/LevelListLoader.cpp
  src/game/LevelListLoader.hpp
  src/game/MovableBlock.cpp
  src/game/MovableBlock.hpp
  src/game/MovingBlock.cpp
  src/game/MovingBlock.hpp
  src/game/Particule.cpp
  src/game/Particule.hpp
  src/game/Pic.cpp
  src/game/Pic.hpp
  src/game/Pincette.cpp
  src/game/Pincette.hpp
  src/game/Resource.cpp
  src/game/Resource.hpp
  src/game/SaveManager.cpp
  src/game/SaveManager.hpp
  src/game/Special.cpp
  src/game/Special.hpp
  src/game/StaticMirror.cpp
  src/game/StaticMirror.hpp
  src/game/Teleporter.cpp
  src/game/Teleporter.hpp
  src/game/TextPopup.cpp
  src/game/TextPopup.hpp
  src/main.cpp
)

target_compile_options(inthecube PRIVATE -Wall -Wextra -pedantic -Werror)

target_include_directories(inthecube PRIVATE ./src)

target_compile_options(inthecube
 PRIVATE
  -Wall
  -Werror
  -pedantic-errors
  -Wextra
)

set_property(TARGET inthecube PROPERTY CXX_STANDARD 17)
add_definitions(-DGLM_FORCE_RADIANS)

# Detect emscripten is used.
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
  target_link_libraries(inthecube PRIVATE -lidbfs.js)

  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " -s DEMANGLE_SUPPORT=1")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " -s DISABLE_EXCEPTION_CATCHING=2")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " -s WASM=1")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " -s TOTAL_MEMORY=134217728")

  # Release flags
  #set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " --closure 1")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " --js-opts 3")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " --llvm-lto 3")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " --llvm-opts 3")
  set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " -O3")

  option(ADD_GOOGLE_ANALYTICS "Add google analytics script" ON)
  if (ADD_GOOGLE_ANALYTICS)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/src/google-analytics.html google-analytics)
  endif(ADD_GOOGLE_ANALYTICS)

  # Copy the index.html file.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
  )

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/style.css
    ${CMAKE_CURRENT_BINARY_DIR}/style.css
  )

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/img/img_hero.png
    ${CMAKE_CURRENT_BINARY_DIR}/favicon.png
    COPYONLY
  )

  # Allow some files to be fetched.
  file(GLOB files "./resources/*" "./resources/*/*")
  foreach(file ${files})
    file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${file})
    set_property(TARGET inthecube APPEND_STRING PROPERTY LINK_FLAGS  " --preload-file ${file}@/${relative_file}")
  endforeach()
else()
  target_link_libraries(inthecube PRIVATE stdc++fs)
endif()

target_link_libraries(inthecube PRIVATE smk)

install(TARGETS inthecube RUNTIME DESTINATION "bin")
install(DIRECTORY resources DESTINATION share/inthecube)

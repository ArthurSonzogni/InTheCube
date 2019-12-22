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
  src/Accelerator.cpp
  src/Accelerator.hpp
  src/Arrow.cpp
  src/Arrow.hpp
  src/Laser.cpp
  src/Laser.hpp
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
endif()

target_link_libraries(inthecube PRIVATE smk)

install(TARGETS inthecube RUNTIME DESTINATION "bin")
install(DIRECTORY resources DESTINATION share/inthecube)

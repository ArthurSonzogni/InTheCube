// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/Main.hpp"

#include <experimental/filesystem>
#include <smk/Audio.hpp>

#include "game/Resource.hpp"

int main() {
  smk::Audio audio;
  std::locale::global(std::locale("C.UTF-8"));

#ifdef __EMSCRIPTEN__
  // clang-format off
  EM_ASM(
      FS.mkdir('/sav');
      FS.mount(IDBFS, {}, '/sav');
      FS.syncfs(true, function(err){console.log("IndexDB synced", err)});
  , 0);
  // clang-format on
#else
  std::experimental::filesystem::create_directory(SavePath());
#endif

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(&MainLoop, 0, 1);
#else
  while (1)
    MainLoop();
#endif
  return EXIT_SUCCESS;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/Main.hpp"

#include <filesystem>
#include <smk/Audio.hpp>

#include "game/Resource.hpp"

int main() {
  static smk::Audio audio;
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
  std::filesystem::create_directory(SavePath());
#endif

  static Main main;
  main.Run();
  return EXIT_SUCCESS;
}

#ifndef SMK_SOUND_BUFFER_HPP
#define SMK_SOUND_BUFFER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <smk/Audio.hpp>
#include <string>

namespace smk {
class Sound;
class SoundBuffer : public Audio {
 public:
  SoundBuffer();  // Empty sound buffer
  SoundBuffer(const std::string filename);

  ~SoundBuffer();

  void Play();

  // --- Move only resource ----------------------------------------------------
  SoundBuffer(SoundBuffer&&);
  SoundBuffer(const SoundBuffer&) = delete;
  void operator=(SoundBuffer&&);
  void operator=(const SoundBuffer&) = delete;
  // ---------------------------------------------------------------------------

  ALuint buffer = 0;
};
}  // namespace smk

#endif /* end of include guard: SMK_SOUND_BUFFER_HPP */
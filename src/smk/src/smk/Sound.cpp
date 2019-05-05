#include <smk/Sound.hpp>
#include <iostream>

namespace smk {

Sound::Sound() {
  alGenSources(1, &source_);
}

Sound::~Sound() {
  Stop();
  if (source_)
    alDeleteSources(1, &source_);
}

void Sound::SetBuffer(const SoundBuffer& buffer) {
  if (buffer_ == &buffer)
    return;
  Stop();
  buffer_ = &buffer;
}

void Sound::Play() {
  if (!source_ || !buffer_ || !buffer_->buffer || is_playing_)
    return;
  alSourcei(source_, AL_BUFFER, buffer_->buffer);
  alSourcePlay(source_);
  is_playing_ = true;
}

void Sound::Stop() {
  if (!source_ || !buffer_ || !is_playing_)
    return;
  alSourceStop(source_);
  alSourcei(source_, AL_BUFFER, 0);
  is_playing_ = false;
}

void Sound::SetLoop(bool looping) {
  alSourcei(source_, AL_LOOPING, looping);
}

Sound::Sound(Sound&& o) {
  operator=(std::move(o));
}

void Sound::operator=(Sound&& o) {
  std::swap(buffer_, o.buffer_);
  std::swap(source_, o.source_);
  std::swap(is_playing_, o.is_playing_);
}

void Sound::SetVolume(float volume) {
  if (!source_)
    return;
  alSourcef(source_, AL_GAIN, volume);
}

}  // namespace smk 
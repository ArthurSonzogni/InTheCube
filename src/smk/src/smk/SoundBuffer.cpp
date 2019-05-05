#include <libnyquist/Decoders.h>
#include <iostream>
#include <smk/SoundBuffer.hpp>
#include <vector>

namespace smk {
SoundBuffer::SoundBuffer() {}

SoundBuffer::SoundBuffer(const std::string filename) {
  nqr::AudioData fileData;
  nqr::NyquistIO loader;
  loader.Load(&fileData, filename);

  ALsizei size =
      static_cast<ALsizei>(fileData.channelCount * fileData.frameSize);
  ALsizei sample_rate = static_cast<ALsizei>(fileData.sampleRate);

  const float mult = 128 * 128;
  std::vector<ALshort> data;
  int i = 0;
  for (auto& it : fileData.samples) {
    data.push_back(128 + it * mult);
  }

  // clang-format off
  ALenum format;
  switch (fileData.channelCount) {
    case 1: format = AL_FORMAT_MONO16; break;
    case 2: format = AL_FORMAT_STEREO16; break;
    default: std::cerr << "SoundBuffer: Unsupported format" << std::endl;
      return;
  }
  // clang-format on.

  alGenBuffers(1, &buffer);
  alBufferData(buffer, format, data.data(), data.size() * sizeof(ALshort), sample_rate);

  if (alGetError() != AL_NO_ERROR) {
    std::cerr << "SoundBuffer: OpenAL error" << std::endl;
    return;
  }
}

SoundBuffer::~SoundBuffer() {
  if (buffer)
    alDeleteBuffers(1, &buffer);
}

SoundBuffer::SoundBuffer(SoundBuffer&& o) {
  this->operator=(std::move(o));
}

void SoundBuffer::operator=(SoundBuffer&& o) {
  std::swap(buffer, o.buffer);
}

}  // namespace smk
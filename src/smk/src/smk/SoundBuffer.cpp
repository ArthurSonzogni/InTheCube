#include <smk/SoundBuffer.hpp>
#include <sndfile.h>
#include <iostream>
#include <vector>

namespace smk {
SoundBuffer::SoundBuffer() {}

SoundBuffer::SoundBuffer(const std::string filename) {
  // Open the file using sndfile.
  SF_INFO file_infos;
  SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &file_infos);
  if (!file) {
    std::cerr << "SoundBuffer: failed to read " << filename << std::endl;
    return;
  }

  ALsizei size = static_cast<ALsizei>(file_infos.channels * file_infos.frames);
  ALsizei sample_rate = static_cast<ALsizei>(file_infos.samplerate);

  std::vector<ALshort> data(size);
  int size_read = sf_read_short(file, &data[0], size);
  sf_close(file);
  if (size_read < size) {
    std::cerr << filename << "SoundBuffer: internal format not supported"
              << std::endl;
    return;
  }

  // clang-format off
  ALenum Format;
  switch (file_infos.channels) {
    case 1: Format = AL_FORMAT_MONO16; break;
    case 2: Format = AL_FORMAT_STEREO16; break;
    default:
      std::cerr << "SoundBuffer: Unsupported format" << std::endl;
      return;
  }
  // clang-format on.

  ALuint buffer;
  alGenBuffers(1, &buffer);
  alBufferData(buffer, Format, &data[0], size * sizeof(ALushort), sample_rate);

  if (alGetError() != AL_NO_ERROR) {
    std::cerr << "SoundBuffer: OpenAL error" << std::endl;
    return;
  }

  std::cerr << "Successfully read " << filename << std::endl;
  buffer_ = buffer;

  /*
  // Création d'une source
  ALuint Source;
  alGenSources(1, &Source);

  // On attache le tampon contenant les échantillons audio à la source
  alSourcei(Source, AL_BUFFER, buffer);

  // Lecture du son
  alSourcePlay(Source);


  ALint Status;
  do {
    // Récupération et affichage de la position courante de lecture en secondes
    ALfloat Seconds = 0.f;
    alGetSourcef(Source, AL_SEC_OFFSET, &Seconds);
    std::cout << "\rLecture en cours... " << std::fixed << std::setprecision(2)
              << Seconds << " sec";

    // Récupération de l'état du son
    alGetSourcei(Source, AL_SOURCE_STATE, &Status);
  } while (Status == AL_PLAYING);


  // Destruction du tampon
  alDeleteBuffers(1, &buffer);

  // Destruction de la source
  alSourcei(Source, AL_BUFFER, 0);
  alDeleteSources(1, &Source);
  */
}

void SoundBuffer::Play() {
  // Création d'une source
	ALuint Source;
	alGenSources(1, &Source);
	alSourcei(Source, AL_BUFFER, buffer_);
  alSourcePlay(Source);
}

SoundBuffer::~SoundBuffer() {}

SoundBuffer::SoundBuffer(SoundBuffer&&) {}

void SoundBuffer::operator=(SoundBuffer&&) {}

}  // namespace smk

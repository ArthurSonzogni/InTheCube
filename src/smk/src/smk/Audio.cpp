#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <smk/Audio.hpp>

#include <vector>
#include <string>
#include <cstring>
namespace smk {

namespace {
ALCdevice* audioDevice = nullptr;
ALCcontext* audioContext = nullptr;
int users = 0;

void GetDevices(std::vector<std::string>& Devices) {
  // Vidage de la liste
  Devices.clear();

  // Récupération des devices disponibles
  const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

  if (DeviceList) {
    // Extraction des devices contenus dans la chaîne renvoyée
    while (std::strlen(DeviceList) > 0) {
      Devices.push_back(DeviceList);
      DeviceList += std::strlen(DeviceList) + 1;
    }
  }
}

}  // namespace

void Audio::IncreaseRef() {
  if (users++)
    return;

  std::vector<std::string> devices;
  GetDevices(devices);
  for (auto& it : devices)
    std::cerr << "Audio devices found: " << it << std::endl;

  audioDevice = alcOpenDevice(devices[0].c_str());
  if (!audioDevice) {
    std::cerr << "Failed to get an OpenAL device. Please check you have some "
                 "backend configured while building your application. For "
                 "instance PulseAudio with libpulse-dev"
              << std::endl;
    return;
  }

  audioContext = alcCreateContext(audioDevice, nullptr);
  if (!audioContext) {
    std::cerr << "Failed to get an OpenAL context" << std::endl;
    return;
  }

  if (!alcMakeContextCurrent(audioContext)) {
    std::cerr << "Failed to make the OpenAL context active" << std::endl;
    return;
  }
}

void Audio::DecreaseRef() {
  if (--users)
    return;

  // Destroy the context
  alcMakeContextCurrent(nullptr);
  if (audioContext) {
    alcDestroyContext(audioContext);
    audioContext = nullptr;
  }

  // Destroy the device
  if (audioDevice) {
    alcCloseDevice(audioDevice);
    audioContext = nullptr;
  }
}

}  // namespace smk
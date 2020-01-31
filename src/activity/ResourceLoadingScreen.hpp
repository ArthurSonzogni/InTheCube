#ifndef ACTIVITY_RESOURCE_LOADING_SCREEN_HPP
#define ACTIVITY_RESOURCE_LOADING_SCREEN_HPP

#include "game/Resource.hpp"
#include "activity/Activity.hpp"

class ResourceLoadingScreen : public Activity {
 public:
  ResourceLoadingScreen(smk::Window& window) : Activity(window) {}
  ~ResourceLoadingScreen() override = default;

  void Draw() override;
  std::function<void()> on_desktop_device = [] {};
  std::function<void()> on_touch_device = [] {};

 private:
  ResourceInitializer initializer;
  float time = 0.f;
};

#endif /* end of include guard: ACTIVITY_RESOURCE_LOADING_SCREEN_HPP */

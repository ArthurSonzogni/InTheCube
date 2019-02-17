/**
 * Main.cpp skeleton
 * Contributors:
 *      * Arthur Sonzogni
 * Licence:
 *      * MIT
 */

#include "MyApplication.hpp"
#include <iostream>

#include "resource.hpp"

int main(int argc, const char* argv[]) {
  MyApplication app;
  initRessource();
  app.run();
  return 0;
}

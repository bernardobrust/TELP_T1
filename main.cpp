#include "App.hxx"

auto main() -> int {
  App app;
  app.init();
  app.run();
  return app.cleanup();
}

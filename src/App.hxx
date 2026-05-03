#pragma once

class App {
  static auto tick() -> void;
  static auto render() -> void;

 public:
  App() = default;
  ~App() = default;

  static auto init() -> void;
  static auto run() -> void;
  static auto cleanup() -> int;
};
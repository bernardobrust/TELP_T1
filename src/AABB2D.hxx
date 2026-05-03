#pragma once

/*
    AABB collision structure for 2d circles.
    This is an important piece for the BVH.
*/

#include <algorithm>
#include <numbers>
#include <utility>

class AABB2D {
 public:
  std::pair<float, float> min_coords{}, max_coords{};

  explicit AABB2D(float min_x, float min_y, float max_x, float max_y)
      : min_coords(min_x, min_y), max_coords(max_x, max_y) {};
  explicit AABB2D(std::pair<float, float> min_c, std::pair<float, float> max_c)
      : min_coords(min_c), max_coords(max_c) {};

  auto __attribute__((always_inline)) contains_point(const float x,
                                                     const float y) const
      -> bool {
    return x >= min_coords.first && x <= max_coords.first &&
           y >= min_coords.second && y <= max_coords.second;
  }
  auto __attribute__((always_inline)) contains_point(
      const std::pair<float, float>& coords) const -> bool {
    return coords.first >= min_coords.first &&
           coords.first <= max_coords.first &&
           coords.second >= min_coords.second &&
           coords.second <= max_coords.second;
  }

  auto __attribute__((always_inline)) interesects(const AABB2D& other) const
      -> bool {
    return min_coords.first <= other.max_coords.first &&
           max_coords.first >= other.min_coords.first &&
           min_coords.second <= other.max_coords.second &&
           max_coords.second >= other.min_coords.second;
  }

  auto __attribute__((always_inline)) get_area() const -> float {
    return (max_coords.first - min_coords.first) *
           (max_coords.second - min_coords.second);
  }
  auto __attribute__((always_inline)) get_perimiter() const -> float {
    return 2.0f * (max_coords.first - min_coords.first + max_coords.second -
                   min_coords.second);
  }

  static AABB2D merge(const AABB2D& a, const AABB2D& b) {
    return AABB2D(std::min(a.min_coords.first, b.min_coords.first),
                  std::min(a.min_coords.second, b.min_coords.second),
                  std::max(a.max_coords.first, b.max_coords.first),
                  std::max(a.max_coords.second, b.max_coords.second));
  }
};

class Circle {
  constexpr static float PI = std::numbers::pi;
  std::pair<float, float> center{};
  const float radius{};

  explicit Circle(float cx, float cy, float r) : center(cx, cy), radius(r) {};

  auto __attribute__((always_inline)) contains_point(const float x,
                                                     const float y)
      -> bool const {
    const float dx = x - center.first, dy = y - center.second;
    return dx * dx + dy * dy <= radius * radius;
  }

  // Smallest AABB enclosing the circle
  auto to_aabb() -> AABB2D const {
    return AABB2D(center.first - radius, center.second - radius,
                  center.first + radius, center.second + radius);
  }
};
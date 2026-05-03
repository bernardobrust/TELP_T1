#pragma once

#include <array>
#include <memory>
#include <span>
#include <utility>

#include "Ball.hxx"

/*
    Bounding volume hierarchy, a tree-based data structure for performing
   volume-based operations efficiently. Here, we're specifically interested in
   collision detection. Check @analysis/TELPKeyIdeas for the detatils relevant
   to this project.

    Source: https://en.wikipedia.org/wiki/Bounding_volume_hierarchy

    Complexity (assuming the tree is not degenerate):
    Construction from vector: O(n*log(n))
    Deletion: O(log(n))
    Lookup: O(log(n))
    Bulk lookup: O(k + log(n))
    Move: O(log(n))
    Storage: O(n)

    We are not woried about insertion as the whole construction happens in the
   start.
*/

// We could template this BVH, but we are just using "Ball" so let's skip the
// formalisms of generic programming
struct BVHNode {
  // We give an id to each volume
  unsigned id{};
  std::unique_ptr<Ball> node{};
  std::array<Ball, 2> children;
};

class BVH {
 private:
 public:
  // Constructed from a span-derived structure
  explicit BVH(std::span<Ball>& balls);

  // We want to be able to lookup a ball given it's coordinates
  auto lookup(float x, float y) -> Ball;
  auto lookup(std::pair<float, float> coords) -> Ball;

  ~BVH() = default;
};
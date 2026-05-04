#pragma once

#include <array>
#include <span>
#include <utility>
#include <vector>

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

   We will be storing the ID of each volume in the nodes, it will reference a
   global array of Balls. This allows for contiguous memory access on what would
   otherwise be a sparse datastructure. This way we can leverage cache.
*/

// We could template this BVH, but we are just using "Ball" so let's skip the
// formalisms of generic programming
struct BVHNode {
  unsigned m_id{};
  std::array<unsigned, 2> m_children;
};

class BVH {
 private:
  static std::vector<Ball> m_balls;

 public:
  // Constructed from a span-derived structure
  explicit BVH(const std::span<Ball>& balls);
  ~BVH() = default;

  // We want to be able to lookup a ball given it's coordinates
  auto lookup(const float x, const float y) -> Ball;
  auto lookup(const std::pair<float, float> coords) -> Ball;
};
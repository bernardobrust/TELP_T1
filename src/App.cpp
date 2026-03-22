//
// Created by be on 3/22/26.
//

#include "App.h"

#include <numeric>
#include <vector>
#include <print>

#include "add_vecs.h"

auto App::init() -> void {}

auto App::run() -> void {
    const std::vector<int> v1 = {1, 2, 3}, v2 = {4, 5, 6};
    const std::vector<int> v3 = add_vecs(v1, v2);

    std::println("Sum: {}", std::accumulate(v3.begin(), v3.end(), 0));
}

auto App::cleanup() -> void {}

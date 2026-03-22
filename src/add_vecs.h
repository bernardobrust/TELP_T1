//
// Created by be on 3/15/26.
//

#ifndef TELP_T1_VECTOR_ADDITION_H
#define TELP_T1_VECTOR_ADDITION_H

#include <vector>
#include <algorithm>
#include <execution>

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<typename T> requires Numeric<T>
auto add_vecs(const std::vector<T> &v1, const std::vector<T> &v2) -> std::vector<T> {
    if (v1.size() != v2.size())
        throw std::invalid_argument("Vectors must have the same size");

    std::vector<T> result(v1.size());
    std::ranges::transform(v1, v2, result.begin(), std::plus<T>{});
    return result;
}

template<typename T> requires Numeric<T>
auto add_vecs_parallel(const std::vector<T> &v1, const std::vector<T> &v2) -> std::vector<T> {
    if (v1.size() != v2.size())
        throw std::invalid_argument("Vectors must have the same size");

    std::vector<T> result(v1.size());
    std::transform(std::execution::par_unseq, v1.begin(), v1.end(), v2.begin(), result.begin(), std::plus<T>{});
    return result;
}
#endif //TELP_T1_VECTOR_ADDITION_H

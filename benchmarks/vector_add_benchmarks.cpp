//
// Created by be on 3/15/26.
//

#include <benchmark/benchmark.h>
#include "../src/add_vecs.h"

static std::vector<int> make_vec(const int size) {
    std::vector<int> v(size);
    std::ranges::iota(v, 0);
    return v;
}

static void BM_VectorAdd(benchmark::State& state) {
    const auto a = make_vec(state.range(0));
    const auto b = make_vec(state.range(0));

    for ([[maybe_unused]] auto _ : state) {
        auto result = add_vecs(a, b);
        benchmark::DoNotOptimize(result);  // prevent the compiler from optimizing the call away
        benchmark::ClobberMemory();        // force result to be written to memory
    }

    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
}

static void BM_VectorAddParallel(benchmark::State& state) {
    const auto a = make_vec(state.range(0));
    const auto b = make_vec(state.range(0));

    for ([[maybe_unused]] auto _ : state) {
        auto result = add_vecs_parallel(a, b);
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
}

BENCHMARK(BM_VectorAdd)
    ->RangeMultiplier(4)
    ->Range(256, 65536)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK(BM_VectorAddParallel)
    ->RangeMultiplier(4)
    ->Range(256, 65536)
    ->Unit(benchmark::kMicrosecond)
    ->UseRealTime();

BENCHMARK(BM_VectorAdd)->Arg(100000)->Name("BM_VectorAdd/fixed_100k");
BENCHMARK(BM_VectorAddParallel)->Arg(100000)->Name("BM_VectorAddParallel/fixed_100k");
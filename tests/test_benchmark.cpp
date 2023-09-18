// Given to the Public Domain by Pyarelal Knowles under CC0 1.0 Universal

#include <cstddef>
#include <iterator>
#define ANKERL_NANOBENCH_IMPLEMENT
#include <algorithm>
#include <gtest/gtest.h>
#include <my_container.hpp>
#include <nanobench.h>
#include <random>
#include <ranges>
#include <string>

using namespace ankerl;

using namespace container_boilerplate;

TEST(Benchmark, ProofOfConcept) {
    const int            n = 10000;
    my_container<int, n> a;
    std::array<int, n>   b;
    auto                 range = std::views::iota(0u, (uint32_t)n);

    std::ranges::copy(range, a.begin());
    std::ranges::copy(range, b.begin());

    uint32_t sum0 = 0;
    nanobench::Bench()
        .minEpochTime(std::chrono::milliseconds(10))
        .run("my_container", [&] {
            sum0 = std::accumulate(a.begin(), a.end(), 0);
            ankerl::nanobench::doNotOptimizeAway(sum0);
        });

    uint32_t sum1 = 0;
    nanobench::Bench()
        .minEpochTime(std::chrono::milliseconds(10))
        .run("std::array", [&] {
            sum1 = std::accumulate(b.begin(), b.end(), 0);
            ankerl::nanobench::doNotOptimizeAway(sum1);
        });

    EXPECT_EQ(sum0, sum1);
}

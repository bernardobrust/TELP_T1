//
// Created by be on 3/15/26.
//

#include <gtest/gtest.h>

#include "../src/add_vecs.h"

class VectorAddFixture : public ::testing::Test {
protected:
    void SetUp() override {
        a = {1, 2, 3};
        b = {4, 5, 6};
        c = {3.14, 1.61, 2.71};
        d = {3.14, 1.61, 2.71};
        e = {0, 1};
    }

    void TearDown() override {
    }

    std::vector<int> a, b, e;
    std::vector<float> c, d;
};

TEST_F(VectorAddFixture, AddsElementWise) {
    const auto result = add_vecs(a, b);
    EXPECT_EQ(result, (std::vector<int>{5, 7, 9}));
}

TEST_F(VectorAddFixture, DoesNotMutateInputs) {
    const auto aCopy = a;
    const auto bCopy = b;
    add_vecs(a, b);
    EXPECT_EQ(a, aCopy);
    EXPECT_EQ(b, bCopy);
}

TEST_F(VectorAddFixture, ThrowsOnSizeMismatch) {
    EXPECT_THROW(add_vecs(a, e), std::invalid_argument);
}

TEST_F(VectorAddFixture, AddsElementWiseParallel) {
    const auto result = add_vecs_parallel(a, b);
    EXPECT_EQ(result, (std::vector<int>{5, 7, 9}));
}

TEST_F(VectorAddFixture, DoesNotMutateInputsParallel) {
    const auto aCopy = a;
    const auto bCopy = b;
    add_vecs_parallel(a, b);
    EXPECT_EQ(a, aCopy);
    EXPECT_EQ(b, bCopy);
}

TEST_F(VectorAddFixture, ThrowsOnSizeMismatchParallel) {
    EXPECT_THROW(add_vecs_parallel(a, e), std::invalid_argument);
}
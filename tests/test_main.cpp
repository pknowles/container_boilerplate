// Given to the Public Domain by Pyarelal Knowles under CC0 1.0 Universal

#include <bitset>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <ranges>
#include <my_container.hpp>

using namespace container_boilerplate;

// iterator verification
template <class iterator>
concept input_and_output_iterator =
    std::input_iterator<iterator> &&
    std::output_iterator<iterator,
                         typename std::iterator_traits<iterator>::value_type>;

// container verification
template <class container>
concept verify_container =
    std::ranges::random_access_range<my_container<int, 10>> &&
    std::ranges::sized_range<my_container<int, 10>> &&
    input_and_output_iterator<typename my_container<int, 10>::iterator>;

static_assert(verify_container<my_container<int, 32>>);
static_assert(verify_container<my_container<char*, 128>>);


// Copy construction
static_assert(std::is_copy_constructible_v<my_container<int, 32>>);
static_assert(std::is_trivially_copy_constructible_v<my_container<int, 32>>);

// Const conversion
//static_assert(std::is_constructible_v<my_container<const int, 32>, my_container<int, 32>>,
//                "can't make const view from non-const view");
static_assert(!std::is_constructible_v<my_container<int, 32>, my_container<const int, 32>>,
                "can make non-const view from const view");

void printCharArrayInBinary(const uint8_t* arr, std::size_t size,
                            std::size_t bytesPerLine = 4) {
  for (std::size_t i = 0; i < size; i += bytesPerLine) {
    std::cout << std::setw(4) << std::hex << i
              << ": "; // Print byte number in hexadecimal
    for (std::size_t j = i; j < i + bytesPerLine && j < size; ++j) {
      std::bitset<8> binaryChar(arr[j]);
      std::cout << binaryChar << ' ';
    }
    std::cout << '\n';
  }
}

using default_container = my_container<int, 5>;

// Test case for the default constructor
TEST(ContainerTest, DefaultConstructor) {
    default_container container;
    EXPECT_EQ(container.size(), 5);
}

TEST(ContainerTest, InitializerListConstructor) {
    default_container container = {0, 1, 2, 3, 4};
    EXPECT_EQ(container.size(), 5);
    EXPECT_EQ(std::ranges::distance(container.begin(), container.end()), 5);
    EXPECT_EQ(std::ranges::distance(container), 5);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
    EXPECT_EQ(container[2], 2);
    EXPECT_EQ(container[3], 3);
    EXPECT_EQ(container[4], 4);
}

TEST(ContainerTest, ReadIteration) {
    default_container container = {0, 1, 2, 3, 4};
    auto it = container.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it, 2);
    it = it + 1;
    EXPECT_EQ(*it, 3);
    it -= 100;
    it += 101;
    it = it - 100;
    it = it + 100;
    EXPECT_EQ(*it, 4);
}

TEST(ContainerTest, WriteIteration) {
    default_container container = {99, 99, 99, 99, 99};
    auto it = container.begin();
    *it = 0;
    ++it;
    *it = 1;
    *it++ = 1;
    *it = 2;
    it = it + 1;
    *it = 3;
    it -= 100;
    it += 101;
    it = it - 100;
    it = it + 100;
    *it = 4;
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
    EXPECT_EQ(container[2], 2);
    EXPECT_EQ(container[3], 3);
    EXPECT_EQ(container[4], 4);
}

TEST(ContainerTest, ReadStdCopy) {
    default_container container = {0, 1, 2, 3, 4};
    std::vector copy(container.begin(), container.end());
    EXPECT_EQ(copy[0], 0);
    EXPECT_EQ(copy[1], 1);
    EXPECT_EQ(copy[2], 2);
    EXPECT_EQ(copy[3], 3);
    EXPECT_EQ(copy[4], 4);
}

TEST(ContainerTest, ReadStdRangesCopy) {
    default_container container = {0, 1, 2, 3, 4};
    std::vector copy(5, 0);
    std::ranges::copy(container, copy.begin());
    EXPECT_EQ(copy[0], 0);
    EXPECT_EQ(copy[1], 1);
    EXPECT_EQ(copy[2], 2);
    EXPECT_EQ(copy[3], 3);
    EXPECT_EQ(copy[4], 4);
}

TEST(ContainerTest, InitializeIteratorRange) {
    std::vector original{0, 1, 2, 3, 4};
    default_container container(original);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
    EXPECT_EQ(container[2], 2);
    EXPECT_EQ(container[3], 3);
    EXPECT_EQ(container[4], 4);
}

// Test case for the copy constructor
TEST(ContainerTest, CopyConstructor) {
    default_container original{42, 0, 0, 0, 0};
    EXPECT_EQ(original[0], 42);
    default_container copy(original);
    EXPECT_EQ(copy[0], 42);
}

// Test case for begin/end iteration of a container with 5 items
TEST(ContainerTest, ContainerWithItemsIteration) {
    default_container container = {0, 1, 2, 3, 4};
    auto beginIt = container.begin();
    auto endIt = container.end();

    EXPECT_NE(beginIt, endIt);
    EXPECT_EQ(*beginIt, 0);

    // Iterate through the container
    uint32_t expectedValue = 0;
    for (auto it = beginIt; it != endIt; ++it) {
        EXPECT_EQ(*it, expectedValue);
        ++expectedValue;
    }
}

// Test cases for iterator arithmetic
TEST(ContainerTest, IteratorArithmetic) {
    default_container container = {0, 1, 2, 3, 4};

    // Test iterator arithmetic operations
    auto it = container.begin();
    EXPECT_EQ(it[0], 0);
    EXPECT_EQ(*(it + 1), 1);
    EXPECT_EQ(*(it + 2), 2);
    EXPECT_EQ(*(it + 3), 3);
    EXPECT_EQ(*(it + 4), 4);

    EXPECT_EQ(it[4], 4);

    // Test pre-increment and pre-decrement
    ++it;
    EXPECT_EQ(*it, 1);
    --it;
    EXPECT_EQ(*it, 0);

    // Test post-increment and post-decrement
    auto postIncIt = it++;
    EXPECT_EQ(*postIncIt, 0);
    EXPECT_EQ(*it, 1);

    auto postDecIt = it--;
    EXPECT_EQ(*postDecIt, 1);
    EXPECT_EQ(*it, 0);

    it = container.end();
    EXPECT_EQ(*(it - 1), 4);
    EXPECT_EQ(*(it - 2), 3);
    EXPECT_EQ(*(it - 3), 2);
    EXPECT_EQ(*(it - 4), 1);
    EXPECT_EQ(*(it - 5), 0);
}

TEST(VectorIteratorTests, BeginEnd) {
    default_container v = {1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*(it + 1), 2);
    EXPECT_EQ(*(it + 2), 3);
    EXPECT_EQ(*(it++), 1);
    EXPECT_EQ(*(it--), 2);
    EXPECT_EQ(*it, 1);
}

TEST(VectorIteratorTests, ReverseIterator) {
    default_container v = {1, 2, 3, 4, 5};
    auto rit = std::reverse_iterator(v.end()) + 2;
    EXPECT_EQ(*rit, 3);
    EXPECT_EQ(*(rit + 1), 2);
    EXPECT_EQ(*(rit + 2), 1);
    EXPECT_EQ(*(rit++), 3);
    EXPECT_EQ(*(rit--), 2);
    EXPECT_EQ(*rit, 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

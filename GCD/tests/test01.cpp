#include <gtest/gtest.h>
#include "../include/GCD.hpp"

// Тест для проверки GCD положительных чисел
TEST(GCDTest, PositiveNumbers) {
    EXPECT_EQ(GCD(1, 18), 1);
    EXPECT_EQ(GCD(99, 37), 1);
    EXPECT_EQ(GCD(99, 45), 9);
}

// Тест для проверки GCD с отрицательными числами
TEST(GCDTest, NegativeNumbers) {
    EXPECT_EQ(GCD(-5, -3), 1);
    EXPECT_EQ(GCD(-10, 5), 5);
    EXPECT_EQ(GCD(10, -5), 5);
}

// Тест для проверки случаев с нулём
TEST(GCDTest, ZeroCases) {
    EXPECT_EQ(GCD(0, 0), -1);
    EXPECT_EQ(GCD(100, 0), 100);
    EXPECT_EQ(GCD(0, 100), 100);
}

// Тест для проверки равных чисел
TEST(GCDTest, EqualNumbers) {
    EXPECT_EQ(GCD(5, 5), 5);
    EXPECT_EQ(GCD(-7, -7), 7);
}

// Тест для случаев, когда один аргумент делит другой
TEST(GCDTest, OneDividesOther) {
    EXPECT_EQ(GCD(10, 5), 5);
    EXPECT_EQ(GCD(15, 5), 5);
    EXPECT_EQ(GCD(-20, 5), 5);
    EXPECT_EQ(GCD(100, 25), 25);
}

// Тест для простых чисел и взаимно простых пар
TEST(GCDTest, PrimeNumbers) {
    EXPECT_EQ(GCD(7, 11), 1);
    EXPECT_EQ(GCD(13, 17), 1);
    EXPECT_EQ(GCD(2, 3), 1);
}

// Тест для больших чисел
TEST(GCDTest, LargeNumbers) {
    EXPECT_EQ(GCD(1000000, 500000), 500000);
    EXPECT_EQ(GCD(2147483647, 1), 1);
    EXPECT_EQ(GCD(1000000000, 500000000), 500000000);
}

// Тест для краевых случаев
TEST(GCDTest, EdgeCases) {
    EXPECT_EQ(GCD(1, 1), 1);
    EXPECT_EQ(GCD(1, -1), 1);
    EXPECT_EQ(GCD(-1, -1), 1);
    EXPECT_EQ(GCD(1, 100), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
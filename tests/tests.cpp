#include <gtest/gtest.h>
#include "../include/Hex.hpp"
#include <sstream>

// Тесты для конструкторов

TEST(HexTest, DefaultConstructor) {
    Hex a;
    EXPECT_EQ(a.getSize(), 0);
}

TEST(HexTest, InitializerListConstructor) {
    Hex a = {'1', '2', 'A'};
    EXPECT_EQ(a.getSize(), 3);
    EXPECT_EQ(a.getDigit(0), 'A');
    EXPECT_EQ(a.getDigit(1), '2');
    EXPECT_EQ(a.getDigit(2), '1');
}

TEST(HexTest, InitializerListWithLeadingZeros) {
    Hex a = {'0', '0', '1', '2'};
    EXPECT_EQ(a.getSize(), 2);
    EXPECT_EQ(a.getDigit(0), '2');
    EXPECT_EQ(a.getDigit(1), '1');
}

TEST(HexTest, InitializerListAllZeros) {
    Hex a = {'0', '0'};
    EXPECT_EQ(a.getSize(), 1);
    EXPECT_EQ(a.getDigit(0), '0');
}

TEST(HexTest, InitializerListInvalidChar) {
    EXPECT_THROW(Hex({'G'}), std::logic_error);
}

TEST(HexTest, StringConstructor) {
    Hex a("12A");
    EXPECT_EQ(a.getSize(), 3);
    EXPECT_EQ(a.getDigit(0), 'A');
    EXPECT_EQ(a.getDigit(1), '2');
    EXPECT_EQ(a.getDigit(2), '1');
}

TEST(HexTest, StringWithLeadingZeros) {
    Hex a("0012");
    EXPECT_EQ(a.getSize(), 2);
    EXPECT_EQ(a.getDigit(0), '2');
    EXPECT_EQ(a.getDigit(1), '1');
}

TEST(HexTest, StringAllZeros) {
    Hex a("000");
    EXPECT_EQ(a.getSize(), 1);
    EXPECT_EQ(a.getDigit(0), '0');
}

TEST(HexTest, StringInvalidChar) {
    EXPECT_THROW(Hex("12G"), std::logic_error);
}

TEST(HexTest, VectorConstructor) {
    std::vector<unsigned char> vec = {'1', '2', 'A'};
    Hex a(vec);
    EXPECT_EQ(a.getSize(), 3);
    EXPECT_EQ(a.getDigit(0), 'A');
    EXPECT_EQ(a.getDigit(1), '2');
    EXPECT_EQ(a.getDigit(2), '1');
}

TEST(HexTest, VectorWithLeadingZeros) {
    std::vector<unsigned char> vec = {'0', '0', '1'};
    Hex a(vec);
    EXPECT_EQ(a.getSize(), 1);
    EXPECT_EQ(a.getDigit(0), '1');
}

TEST(HexTest, VectorInvalidChar) {
    std::vector<unsigned char> vec = {'1', 'G'};
    EXPECT_THROW(Hex a(vec), std::logic_error);
}

TEST(HexTest, MoveConstructor) {
    Hex a("12A");
    Hex b(std::move(a));
    EXPECT_EQ(b.getSize(), 3);
    EXPECT_EQ(b.getDigit(0), 'A');
    EXPECT_EQ(b.getDigit(1), '2');
    EXPECT_EQ(b.getDigit(2), '1');
    EXPECT_EQ(a.getSize(), 0);
}

// Тесты для операций

TEST(HexTest, AddSimple) {
    Hex a("1");
    Hex b("2");
    Hex c = a.add(b);
    EXPECT_EQ(c.getSize(), 1);
    EXPECT_EQ(c.getDigit(0), '3');
}

TEST(HexTest, AddWithCarry) {
    Hex a("F");
    Hex b("1");
    Hex c = a.add(b);
    EXPECT_EQ(c.getSize(), 2);
    EXPECT_EQ(c.getDigit(0), '0');
    EXPECT_EQ(c.getDigit(1), '1');
}

TEST(HexTest, AddLargeNumbers) {
    Hex a("FFFF");
    Hex b("1");
    Hex c = a.add(b);
    EXPECT_EQ(c.getSize(), 5);
    EXPECT_EQ(c.getDigit(0), '0');
    EXPECT_EQ(c.getDigit(1), '0');
    EXPECT_EQ(c.getDigit(2), '0');
    EXPECT_EQ(c.getDigit(3), '0');
    EXPECT_EQ(c.getDigit(4), '1');
}

TEST(HexTest, SubtractSimple) {
    Hex a("3");
    Hex b("1");
    Hex c = a.subtract(b);
    EXPECT_EQ(c.getSize(), 1);
    EXPECT_EQ(c.getDigit(0), '2');
}

TEST(HexTest, SubtractWithBorrow) {
    Hex a("10");
    Hex b("1");
    Hex c = a.subtract(b);
    EXPECT_EQ(c.getSize(), 1);
    EXPECT_EQ(c.getDigit(0), 'F');
}

TEST(HexTest, SubtractEqual) {
    Hex a("5");
    Hex b("5");
    Hex c = a.subtract(b);
    EXPECT_EQ(c.getSize(), 1);
    EXPECT_EQ(c.getDigit(0), '0');
}

TEST(HexTest, SubtractNegativeResult) {
    Hex a("1");
    Hex b("2");
    EXPECT_THROW(a.subtract(b), std::logic_error);
}

TEST(HexTest, SubtractLargerFromSmaller) {
    Hex a("1");
    Hex b("10");
    EXPECT_THROW(a.subtract(b), std::logic_error);
}

TEST(HexTest, EqualsTrue) {
    Hex a("12A");
    Hex b("12A");
    EXPECT_TRUE(a.equals(b));
}

TEST(HexTest, EqualsFalse) {
    Hex a("12A");
    Hex b("12B");
    EXPECT_FALSE(a.equals(b));
}

TEST(HexTest, EqualsDifferentSizes) {
    Hex a("1");
    Hex b("01");
    EXPECT_TRUE(a.equals(b));
}

TEST(HexTest, GreaterTrue) {
    Hex a("2");
    Hex b("1");
    EXPECT_TRUE(a.greater(b));
}

TEST(HexTest, GreaterFalse) {
    Hex a("1");
    Hex b("2");
    EXPECT_FALSE(a.greater(b));
}

TEST(HexTest, GreaterEqual) {
    Hex a("1");
    Hex b("1");
    EXPECT_FALSE(a.greater(b));
}

TEST(HexTest, GreaterDifferentSizes) {
    Hex a("100");
    Hex b("FF");
    EXPECT_TRUE(a.greater(b));
}

TEST(HexTest, LessTrue) {
    Hex a("1");
    Hex b("2");
    EXPECT_TRUE(a.less(b));
}

TEST(HexTest, LessFalse) {
    Hex a("2");
    Hex b("1");
    EXPECT_FALSE(a.less(b));
}

TEST(HexTest, LessEqual) {
    Hex a("1");
    Hex b("1");
    EXPECT_FALSE(a.less(b));
}

// Тест для вывода

TEST(HexTest, Print) {
    Hex a("12A");
    std::ostringstream oss;
    a.print(oss);
    EXPECT_EQ(oss.str(), "12A");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
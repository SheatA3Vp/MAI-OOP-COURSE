#include <gtest/gtest.h>
#include "../include/triangle.hpp"
#include "../include/square.hpp"
#include "../include/octagon.hpp"
#include "../include/figure_array.hpp"
#include <sstream>

TEST(TriangleTest, Area) {
    Point points[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle t(points);
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 0.5, 1e-6);
}

TEST(TriangleTest, InvalidCollinear) {
    Point points[3] = {{0, 0}, {1, 0}, {2, 0}};
    EXPECT_THROW(Triangle t(points), std::invalid_argument);
}

TEST(SquareTest, Area) {
    Point points[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square s(points);
    double area = static_cast<double>(s);
    EXPECT_NEAR(area, 1.0, 1e-6);
}

TEST(SquareTest, InvalidNotSquare) {
    Point points[4] = {{0, 0}, {2, 0}, {1, 1}, {0, 2}};
    EXPECT_THROW(Square s(points), std::invalid_argument);
}

TEST(OctagonTest, Area) {
    // Простой октагон
    Point points[8] = {{0, 1}, {1, 2}, {2, 2}, {3, 1}, {3, 0}, {2, -1}, {1, -1}, {0, 0}};
    Octagon o(points);
    double area = static_cast<double>(o);
    EXPECT_NEAR(area, 7.0, 1e-6);
}

TEST(TriangleTest, Center) {
    Point points[3] = {{0, 0}, {2, 0}, {0, 2}};
    Triangle t(points);
    Point c = t.center();
    EXPECT_NEAR(c.x, 2.0/3, 1e-6);
    EXPECT_NEAR(c.y, 2.0/3, 1e-6);
}

TEST(SquareTest, Center) {
    Point points[4] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Square s(points);
    Point c = s.center();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

TEST(TriangleTest, Equals) {
    Point points1[3] = {{0, 0}, {1, 0}, {0, 1}};
    Point points2[3] = {{0, 0}, {1, 0}, {0, 1}};
    Point points3[3] = {{0, 0}, {2, 0}, {0, 1}};
    Triangle t1(points1);
    Triangle t2(points2);
    Triangle t3(points3);
    EXPECT_TRUE(t1.equals(t2));
    EXPECT_FALSE(t1.equals(t3));
}

TEST(FigureTest, EqualsDifferentTypes) {
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle t(tpoints);
    Point spoints[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square s(spoints);
    EXPECT_FALSE(t.equals(s));
    EXPECT_FALSE(s.equals(t));
}

TEST(SquareTest, Equals) {
    Point points1[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Point points2[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Point points3[4] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Square s1(points1);
    Square s2(points2);
    Square s3(points3);
    EXPECT_TRUE(s1.equals(s2));
    EXPECT_FALSE(s1.equals(s3));
}

TEST(TriangleTest, CopyConstructor) {
    Point points[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle t1(points);
    Triangle t2(t1);
    EXPECT_TRUE(t1.equals(t2));
    EXPECT_NEAR(static_cast<double>(t1), static_cast<double>(t2), 1e-6);
}

TEST(TriangleTest, AssignmentOperator) {
    Point points1[3] = {{0, 0}, {1, 0}, {0, 1}};
    Point points2[3] = {{0, 0}, {2, 0}, {0, 2}};
    Triangle t1(points1);
    Triangle t2(points2);
    t2 = t1;
    EXPECT_TRUE(t1.equals(t2));
    EXPECT_NEAR(static_cast<double>(t1), static_cast<double>(t2), 1e-6);
}

TEST(TriangleTest, MoveConstructor) {
    Point points[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle t1(points);
    Triangle t2(std::move(t1));
    EXPECT_NEAR(static_cast<double>(t2), 0.5, 1e-6);
}

TEST(TriangleTest, MoveAssignment) {
    Point points1[3] = {{0, 0}, {1, 0}, {0, 1}};
    Point points2[3] = {{0, 0}, {2, 0}, {0, 2}};
    Triangle t1(points1);
    Triangle t2(points2);
    t2 = std::move(t1);
    EXPECT_NEAR(static_cast<double>(t2), 0.5, 1e-6);
}

TEST(SquareTest, CopyConstructor) {
    Point points[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square s1(points);
    Square s2(s1);
    EXPECT_TRUE(s1.equals(s2));
    EXPECT_NEAR(static_cast<double>(s1), static_cast<double>(s2), 1e-6);
}

TEST(SquareTest, AssignmentOperator) {
    Point points1[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Point points2[4] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Square s1(points1);
    Square s2(points2);
    s2 = s1;
    EXPECT_TRUE(s1.equals(s2));
    EXPECT_NEAR(static_cast<double>(s1), static_cast<double>(s2), 1e-6);
}

TEST(SquareTest, MoveConstructor) {
    Point points[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square s1(points);
    Square s2(std::move(s1));
    EXPECT_NEAR(static_cast<double>(s2), 1.0, 1e-6);
}

TEST(SquareTest, MoveAssignment) {
    Point points1[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Point points2[4] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Square s1(points1);
    Square s2(points2);
    s2 = std::move(s1);
    EXPECT_NEAR(static_cast<double>(s2), 1.0, 1e-6);
}

TEST(TriangleTest, OutputOperator) {
    Point points[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle t(points);
    std::stringstream ss;
    ss << t;
    std::string output = ss.str();
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
}

TEST(TriangleTest, InputOperator) {
    std::stringstream ss("0 0 1 0 0 1");
    Triangle t;
    ss >> t;
    Point expected[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle expected_t(expected);
    EXPECT_TRUE(t.equals(expected_t));
}

TEST(TriangleTest, SortingVertices) {
    Point unsorted[3] = {{0, 1}, {1, 0}, {0, 0}};
    Triangle t_unsorted(unsorted);
    Point sorted[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle t_sorted(sorted);
    EXPECT_TRUE(t_unsorted.equals(t_sorted));
}

TEST(SquareTest, OutputOperator) {
    Point points[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square s(points);
    std::stringstream ss;
    ss << s;
    std::string output = ss.str();
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
}

TEST(SquareTest, InputOperator) {
    std::stringstream ss("0 0 1 0 1 1 0 1");
    Square s;
    ss >> s;
    Point expected[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square expected_s(expected);
    EXPECT_TRUE(s.equals(expected_s));
}

TEST(SquareTest, SortingVertices) {
    Point unsorted[4] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}};
    Square s_unsorted(unsorted);
    Point sorted[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square s_sorted(sorted);
    EXPECT_TRUE(s_unsorted.equals(s_sorted));
}

TEST(FigureArrayTest, AddAndSize) {
    FigureArray arr;
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle* t = new Triangle(tpoints);
    arr.add(*t);
    EXPECT_EQ(arr.get_size(), 1);
    Point spoints[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square* s = new Square(spoints);
    arr.add(*s);
    EXPECT_EQ(arr.get_size(), 2);
}

TEST(FigureArrayTest, Pop) {
    FigureArray arr;
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle* t = new Triangle(tpoints);
    arr.add(*t);
    Point spoints[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square* s = new Square(spoints);
    arr.add(*s);
    EXPECT_EQ(arr.get_size(), 2);
    arr.pop(0);
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(FigureArrayTest, PopInvalidIndex) {
    FigureArray arr;
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle* t = new Triangle(tpoints);
    arr.add(*t);
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray arr;
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle* t = new Triangle(tpoints);
    arr.add(*t);
    Point spoints[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Square* s = new Square(spoints);
    arr.add(*s);
    double total = arr.total_area();
    EXPECT_NEAR(total, 1.5, 1e-6);
}

TEST(FigureArrayTest, CopyConstructor) {
    FigureArray arr1;
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle* t = new Triangle(tpoints);
    arr1.add(*t);
    FigureArray arr2(arr1);
    EXPECT_EQ(arr1.get_size(), arr2.get_size());
    EXPECT_NEAR(arr1.total_area(), arr2.total_area(), 1e-6);
}

TEST(FigureArrayTest, MoveConstructor) {
    FigureArray arr1;
    Point tpoints[3] = {{0, 0}, {1, 0}, {0, 1}};
    Triangle* t = new Triangle(tpoints);
    arr1.add(*t);
    FigureArray arr2(std::move(arr1));
    EXPECT_EQ(arr2.get_size(), 1);
    EXPECT_NEAR(arr2.total_area(), 0.5, 1e-6);
    EXPECT_EQ(arr1.get_size(), 0);
}

TEST(FigureArrayTest, EmptyArray) {
    FigureArray arr;
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_NEAR(arr.total_area(), 0.0, 1e-6);
}

TEST(FigureArrayTest, LargeArray) {
    FigureArray arr;
    for (int i = 0; i < 100; ++i) {
        Point points[3] = {{0, 0}, {1, 0}, {0, 1}};
        Triangle* t = new Triangle(points);
        arr.add(*t);
    }
    EXPECT_EQ(arr.get_size(), 100);
    EXPECT_NEAR(arr.total_area(), 50.0, 1e-6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include "../include/trapezoid.hpp"
#include "../include/rhombus.hpp"
#include "../include/pentagon.hpp"
#include "../include/figure_array.hpp"
#include <sstream>
#include <memory>

// Helper function to create unique_ptr for points
template <typename T>
std::unique_ptr<Point<T>[]> make_points(std::initializer_list<Point<T>> list) {
    auto ptr = std::make_unique<Point<T>[]>(list.size());
    std::copy(list.begin(), list.end(), ptr.get());
    return ptr;
}

// ============== TRAPEZOID TESTS ==============
TEST(TrapezoidTest, Area) {
    auto points = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double> t(std::move(points));
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 9.0, 1e-1);
}

TEST(TrapezoidTest, Center) {
    auto points = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double> t(std::move(points));
    Point<double> c = t.center();
    EXPECT_NEAR(c.x, 2.0, 1e-6);
    EXPECT_NEAR(c.y, 1.5, 1e-6);
}

TEST(TrapezoidTest, NegativeCoordinates) {
    auto points = make_points<double>({{-2, -2}, {2, -2}, {1, 1}, {-1, 1}});
    Trapezoid<double> t(std::move(points));
    double area = static_cast<double>(t);
    EXPECT_GT(area, 0.0);
}

TEST(TrapezoidTest, ZeroCoordinates) {
    auto points = make_points<double>({{0, 0}, {2, 0}, {1.5, 1}, {0.5, 1}});
    Trapezoid<double> t(std::move(points));
    Point<double> c = t.center();
    EXPECT_NEAR(c.y, 0.5, 1e-6);
}

TEST(TrapezoidTest, LargeCoordinates) {
    auto points = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double> t(std::move(points));
    double area = static_cast<double>(t);
    EXPECT_GT(area, 0.0);
}

TEST(TrapezoidTest, SmallCoordinates) {
    auto points = make_points<double>({{0, 0}, {0.001, 0}, {0.0009, 0.0005}, {0.0001, 0.0005}});
    Trapezoid<double> t(std::move(points));
    double area = static_cast<double>(t);
    EXPECT_GT(area, 0.0);
}

// ============== RHOMBUS TESTS ==============
TEST(RhombusTest, Area) {
    auto points = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double> r(std::move(points));
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, 2.0, 1e-6);
}

TEST(RhombusTest, Center) {
    auto points = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double> r(std::move(points));
    Point<double> c = r.center();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 0.0, 1e-6);
}

TEST(RhombusTest, NegativeCoordinates) {
    auto points = make_points<double>({{-1, 0}, {0, -1}, {1, 0}, {0, 1}});
    Rhombus<double> r(std::move(points));
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, 2.0, 1e-6);
}

TEST(RhombusTest, CenterNegative) {
    auto points = make_points<double>({{-2, -2}, {-1, -1}, {0, -2}, {-1, -3}});
    Rhombus<double> r(std::move(points));
    Point<double> c = r.center();
    EXPECT_NEAR(c.x, -1.0, 1e-6);
    EXPECT_NEAR(c.y, -2.0, 1e-6);
}

TEST(RhombusTest, UnitRhombus) {
    auto points = make_points<double>({{0, 0}, {0.5, 0.5}, {1, 0}, {0.5, -0.5}});
    Rhombus<double> r(std::move(points));
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, 0.5, 1e-6);
}

// ============== PENTAGON TESTS ==============
TEST(PentagonTest, Area) {
    auto points = make_points<double>({{1, 0}, {0.309, -0.951}, {-0.809, -0.588}, {-0.809, 0.588}, {0.309, 0.951}});
    Pentagon<double> p(std::move(points));
    double area = static_cast<double>(p);
    EXPECT_NEAR(area, 2.377, 1e-1);
}

TEST(PentagonTest, Center) {
    auto points = make_points<double>({{1, 0}, {0.309, -0.951}, {-0.809, -0.588}, {-0.809, 0.588}, {0.309, 0.951}});
    Pentagon<double> p(std::move(points));
    Point<double> c = p.center();
    EXPECT_NEAR(c.x, 0.0, 1e-1);
    EXPECT_NEAR(c.y, 0.0, 1e-1);
}

TEST(PentagonTest, SimplePentagon) {
    // Правильный пятиугольник с центром в (0, 0) и радиусом 1
    double angle = 2.0 * M_PI / 5.0;
    auto points = make_points<double>({
        {cos(0), sin(0)},
        {cos(angle), sin(angle)},
        {cos(2*angle), sin(2*angle)},
        {cos(3*angle), sin(3*angle)},
        {cos(4*angle), sin(4*angle)}
    });
    Pentagon<double> p(std::move(points));
    double area = static_cast<double>(p);
    EXPECT_GT(area, 0.0);
}

// ============== POINT TESTS ==============
TEST(PointTest, PointEquality) {
    Point<double> p1{1.0, 2.0};
    Point<double> p2{1.0, 2.0};
    Point<double> p3{1.0, 3.0};
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, PointInequality) {
    Point<double> p1{1.0, 2.0};
    Point<double> p2{1.0, 3.0};
    EXPECT_TRUE(p1 != p2);
}

TEST(PointTest, PointAddition) {
    Point<double> p1{1.0, 2.0};
    Point<double> p2{3.0, 4.0};
    Point<double> result = p1 + p2;
    EXPECT_NEAR(result.x, 4.0, 1e-6);
    EXPECT_NEAR(result.y, 6.0, 1e-6);
}

TEST(PointTest, PointSubtraction) {
    Point<double> p1{5.0, 7.0};
    Point<double> p2{2.0, 3.0};
    Point<double> result = p1 - p2;
    EXPECT_NEAR(result.x, 3.0, 1e-6);
    EXPECT_NEAR(result.y, 4.0, 1e-6);
}

TEST(PointTest, PointDivision) {
    Point<double> p{4.0, 6.0};
    Point<double> result = p / 2;
    EXPECT_NEAR(result.x, 2.0, 1e-6);
    EXPECT_NEAR(result.y, 3.0, 1e-6);
}

TEST(PointTest, PointNegativeCoordinates) {
    Point<double> p1{-1.0, -2.0};
    Point<double> p2{1.0, 2.0};
    Point<double> result = p1 + p2;
    EXPECT_NEAR(result.x, 0.0, 1e-6);
    EXPECT_NEAR(result.y, 0.0, 1e-6);
}

TEST(PointTest, PointZeroCoordinates) {
    Point<double> p{0.0, 0.0};
    EXPECT_NEAR(p.x, 0.0, 1e-6);
    EXPECT_NEAR(p.y, 0.0, 1e-6);
}

TEST(PointTest, IntToDoubleConversion) {
    Point<double> p{1, 2}; // int в double
    EXPECT_NEAR(p.x, 1.0, 1e-6);
    EXPECT_NEAR(p.y, 2.0, 1e-6);
}

// ============== ARRAY TESTS ==============
TEST(ArrayTest, EmptyArray) {
    Array<Figure<double>*> arr;
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_NEAR(arr.total_area(), 0.0, 1e-6);
}

TEST(ArrayTest, AddAndSize) {
    Array<Figure<double>*> arr;
    auto points = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double>* t = new Trapezoid<double>(std::move(points));
    arr.add(t);
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(ArrayTest, AddMultipleFigures) {
    Array<Figure<double>*> arr;
    auto points1 = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double>* t = new Trapezoid<double>(std::move(points1));
    arr.add(t);
    auto points2 = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double>* r = new Rhombus<double>(std::move(points2));
    arr.add(r);
    auto points3 = make_points<double>({{1, 0}, {0.309, -0.951}, {-0.809, -0.588}, {-0.809, 0.588}, {0.309, 0.951}});
    Pentagon<double>* p = new Pentagon<double>(std::move(points3));
    arr.add(p);
    EXPECT_EQ(arr.get_size(), 3);
}

TEST(ArrayTest, TotalArea) {
    Array<Figure<double>*> arr;
    auto points1 = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double>* t = new Trapezoid<double>(std::move(points1));
    arr.add(t);
    auto points2 = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double>* r = new Rhombus<double>(std::move(points2));
    arr.add(r);
    double total = arr.total_area();
    EXPECT_NEAR(total, 11.0, 1e-1);
}

TEST(ArrayTest, Pop) {
    Array<Figure<double>*> arr;
    auto points = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double>* t = new Trapezoid<double>(std::move(points));
    arr.add(t);
    EXPECT_EQ(arr.get_size(), 1);
    arr.pop(0);
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(ArrayTest, PopMiddleElement) {
    Array<Figure<double>*> arr;
    auto points1 = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double>* t1 = new Trapezoid<double>(std::move(points1));
    arr.add(t1);
    auto points2 = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double>* r = new Rhombus<double>(std::move(points2));
    arr.add(r);
    auto points3 = make_points<double>({{1, 0}, {0.309, -0.951}, {-0.809, -0.588}, {-0.809, 0.588}, {0.309, 0.951}});
    Pentagon<double>* p = new Pentagon<double>(std::move(points3));
    arr.add(p);
    EXPECT_EQ(arr.get_size(), 3);
    arr.pop(1);
    EXPECT_EQ(arr.get_size(), 2);
}

TEST(ArrayTest, PopLastElement) {
    Array<Figure<double>*> arr;
    auto points1 = make_points<double>({{0, 0}, {4, 0}, {3, 3}, {1, 3}});
    Trapezoid<double>* t = new Trapezoid<double>(std::move(points1));
    arr.add(t);
    auto points2 = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double>* r = new Rhombus<double>(std::move(points2));
    arr.add(r);
    EXPECT_EQ(arr.get_size(), 2);
    arr.pop(1);
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(ArrayTest, SingleElementArray) {
    Array<Figure<double>*> arr;
    auto points = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
    Rhombus<double>* r = new Rhombus<double>(std::move(points));
    arr.add(r);
    double total = arr.total_area();
    EXPECT_NEAR(total, 2.0, 1e-6);
}

TEST(ArrayTest, ManyFigures) {
    Array<Figure<double>*> arr;
    for (int i = 0; i < 10; ++i) {
        auto points = make_points<double>({{0, 0}, {1, 1}, {2, 0}, {1, -1}});
        Rhombus<double>* r = new Rhombus<double>(std::move(points));
        arr.add(r);
    }
    EXPECT_EQ(arr.get_size(), 10);
    double total = arr.total_area();
    EXPECT_NEAR(total, 20.0, 1e-5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

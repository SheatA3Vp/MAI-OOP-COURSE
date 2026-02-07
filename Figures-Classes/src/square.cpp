#include "../include/square.hpp"
#include <cmath>

// Конструкторы
Square::Square() : Figure(SQUARE_VERTICES) {}

Square::Square(Point* verts) : Figure(SQUARE_VERTICES, verts) {
    if (!isSquare()) {
        throw std::invalid_argument("Points do not form a square");
    }
    this->sortVertices();
}

// Конструктор копирования
Square::Square(const Square& other) : Figure(other) {}

// Оператор присваивания копиованием
Square& Square::operator=(const Square& other) {
    Figure::operator=(other);
    return *this;
}

// Конструктор перемещения
Square::Square(Square&& other) noexcept : Figure(std::move(other)) {}

// Конструктор присваивания перемещением
Square& Square::operator=(Square&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

// Геометрический центр (центроид)
Point Square::center() const {
    return Figure::center();
}

// Чтение/запись
void Square::read(std::istream& in) {
    for (size_t i = 0; i < SQUARE_VERTICES; ++i) {
        in >> this->vertices[i];
    }

    if (!isConvex() || !isSquare()) {
        throw std::invalid_argument("Points do not form a convex square");
    }
    this->sortVertices();
}

void Square::write(std::ostream& out) const {
    for (size_t i = 0; i < SQUARE_VERTICES; ++i) {
        Point p = this->vertices[i];
        out << p << " ";
    }
}

// Площадь через приведение к double
Square::operator double() const {
    return Figure::operator double();
}

// Клонирование
Figure* Square::clone() const {
    return new Square(*this);
}

// Проверка на равенство
bool Square::equals(const Figure& other) const {
    return Figure::equals(other);
}

// Проверка квадрата на квадратность
bool Square::isSquare() const {
    if (vertices_num != 4) return false;

    auto distance = [](const Point& a, const Point& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    };

    double side1 = distance(vertices[0], vertices[1]);
    double side2 = distance(vertices[1], vertices[2]);
    double side3 = distance(vertices[2], vertices[3]);
    double side4 = distance(vertices[3], vertices[0]);

    if (side1 != side2 || side2 != side3 || side3 != side4) return false;

    double diag1 = distance(vertices[0], vertices[2]);
    double diag2 = distance(vertices[1], vertices[3]);

    if (diag1 != diag2) return false;

    return true;
}
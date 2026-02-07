#include "../include/triangle.hpp"

// Конструкторы
Triangle::Triangle() : Figure(TRIANGLE_VERTICES) {}

Triangle::Triangle(Point* verts) : Figure(TRIANGLE_VERTICES, verts) {
    if (!isConvex()) {
        throw std::invalid_argument("Triangle is not convex");
    }
    if (static_cast<double>(*this) == 0.0) {
        throw std::invalid_argument("Degenerate triangle");
    }
    this->sortVertices();
}

// Конструктор копирования
Triangle::Triangle(const Triangle& other) : Figure(other) {}

// Оператор присваивания копиованием
Triangle& Triangle::operator=(const Triangle& other) {
    Figure::operator=(other);
    return *this;
}

// Конструктор перемещения
Triangle::Triangle(Triangle&& other) noexcept : Figure(std::move(other)) {}

// Конструктор присваивания перемещением
Triangle& Triangle::operator=(Triangle&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

// Геометрический центр (центроид)
Point Triangle::center() const {
    return Figure::center();
}

// Чтение/запись
void Triangle::read(std::istream& in) {
    for (size_t i = 0; i < TRIANGLE_VERTICES; ++i) {
        in >> this->vertices[i];
    }

    if (!isConvex()) {
        throw std::invalid_argument("Triangle is not convex");
    }
    if (static_cast<double>(*this) == 0.0) {
        throw std::invalid_argument("Degenerate triangle");
    }
    this->sortVertices();
}

void Triangle::write(std::ostream& out) const {
    for (size_t i = 0; i < TRIANGLE_VERTICES; ++i) {
        Point p = this->vertices[i];
        out << p << " ";
    }
}

// Площадь через приведение к double
Triangle::operator double() const {
    return Figure::operator double();
}

// Клонирование
Figure* Triangle::clone() const {
    return new Triangle(*this);
}

// Проверка на равенство
bool Triangle::equals(const Figure& other) const {
    return Figure::equals(other);
}
#include "../include/octagon.hpp"

// Конструкторы
Octagon::Octagon() : Figure(OCTAGON_VERTICES) {}

Octagon::Octagon(Point* verts) : Figure(OCTAGON_VERTICES, verts) {
    if (!isConvex()) {
        throw std::invalid_argument("Octagon is not convex");
    }
    if (static_cast<double>(*this) == 0.0) {
        throw std::invalid_argument("Degenerate octagon");
    }
    this->sortVertices();
}

// Конструктор копирования
Octagon::Octagon(const Octagon& other) : Figure(other) {}

// Оператор присваивания копиованием
Octagon& Octagon::operator=(const Octagon& other) {
    Figure::operator=(other);
    return *this;
}

// Конструктор перемещения
Octagon::Octagon(Octagon&& other) noexcept : Figure(std::move(other)) {}

// Конструктор присваивания перемещением
Octagon& Octagon::operator=(Octagon&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

// Геометрический центр (центроид)
Point Octagon::center() const {
    return Figure::center();
}

// Чтение/запись
void Octagon::read(std::istream& in) {
    for (size_t i = 0; i < OCTAGON_VERTICES; ++i) {
        in >> this->vertices[i];
    }

    if (!isConvex()) {
        throw std::invalid_argument("Octagon is not convex");
    }
    if (static_cast<double>(*this) == 0.0) {
        throw std::invalid_argument("Degenerate octagon");
    }
    this->sortVertices();
}

void Octagon::write(std::ostream& out) const {
    for (size_t i = 0; i < OCTAGON_VERTICES; ++i) {
        Point p = this->vertices[i];
        out << p << " ";
    }
}

// Площадь через приведение к double
Octagon::operator double() const {
    return Figure::operator double();
}

// Клонирование
Figure* Octagon::clone() const {
    return new Octagon(*this);
}

// Проверка на равенство
bool Octagon::equals(const Figure& other) const {
    return Figure::equals(other);
}
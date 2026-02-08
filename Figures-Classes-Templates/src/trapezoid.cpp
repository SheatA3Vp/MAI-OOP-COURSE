#include "../include/trapezoid.hpp"
#include <cmath>

// Конструкторы
template <typename T>
Trapezoid<T>::Trapezoid() : Figure<T>(TRAPEZOID_VERTICES) {}

template <typename T>
Trapezoid<T>::Trapezoid(std::unique_ptr<Point<T>[]> verts) : Figure<T>(TRAPEZOID_VERTICES, std::move(verts)) {
    if (!isTrapezoid()) {
        throw std::invalid_argument("Points do not form a trapezoid inscribed in a circle");
    }
    this->sortVertices();
}

// Конструктор копирования
template <typename T>
Trapezoid<T>::Trapezoid(const Trapezoid& other) : Figure<T>(other) {}

// Оператор присваивания копиованием
template <typename T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other) {
    Figure<T>::operator=(other);
    return *this;
}

// Конструктор перемещения
template <typename T>
Trapezoid<T>::Trapezoid(Trapezoid&& other) noexcept : Figure<T>(std::move(other)) {}

// Конструктор присваивания перемещением
template <typename T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid&& other) noexcept {
    Figure<T>::operator=(std::move(other));
    return *this;
}

// Геометрический центр (центроид)
template <typename T>
Point<T> Trapezoid<T>::center() const {
    return Figure<T>::center();
}

// Чтение/запись
template <typename T>
void Trapezoid<T>::read(std::istream& in) {
    for (size_t i = 0; i < TRAPEZOID_VERTICES; ++i) {
        in >> this->vertices[i];
    }

    if (!this->isConvex() || !isTrapezoid()) {
        throw std::invalid_argument("Points do not form a convex trapezoid inscribed in a circle");
    }
    this->sortVertices();
}

template <typename T>
void Trapezoid<T>::write(std::ostream& out) const {
    for (size_t i = 0; i < TRAPEZOID_VERTICES; ++i) {
        Point<T> p = this->vertices[i];
        out << p << " ";
    }
}

// Площадь через приведение к double
template <typename T>
Trapezoid<T>::operator double() const {
    return Figure<T>::operator double();
}

// Клонирование
template <typename T>
Figure<T>* Trapezoid<T>::clone() const {
    return new Trapezoid(*this);
}

// Проверка на равенство
template <typename T>
bool Trapezoid<T>::equals(const Figure<T>& other) const {
    return Figure<T>::equals(other);
}

// Проверка трапеции на вписанность в круг
template <typename T>
bool Trapezoid<T>::isTrapezoid() const {
    if (this->vertices_num != 4) return false;

    auto distance = [](const Point<T>& a, const Point<T>& b) {
        double dx = static_cast<double>(a.x) - static_cast<double>(b.x);
        double dy = static_cast<double>(a.y) - static_cast<double>(b.y);
        return sqrt(dx * dx + dy * dy);
    };

    double side1 = distance(this->vertices[0], this->vertices[1]);
    double side2 = distance(this->vertices[1], this->vertices[2]);
    double side3 = distance(this->vertices[2], this->vertices[3]);
    double side4 = distance(this->vertices[3], this->vertices[0]);

    // For trapezoid inscribed in circle, sum of opposite sides equal
    return fabs((side1 + side3) - (side2 + side4)) < 1e-6;
}

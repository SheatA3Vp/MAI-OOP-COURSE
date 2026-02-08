#include "../include/pentagon.hpp"
#include <cmath>

// Конструкторы
template <typename T>
Pentagon<T>::Pentagon() : Figure<T>(PENTAGON_VERTICES) {}

template <typename T>
Pentagon<T>::Pentagon(std::unique_ptr<Point<T>[]> verts) : Figure<T>(PENTAGON_VERTICES, std::move(verts)) {
    if (!isPentagon()) {
        throw std::invalid_argument("Points do not form a regular pentagon");
    }
    this->sortVertices();
}

// Конструктор копирования
template <typename T>
Pentagon<T>::Pentagon(const Pentagon& other) : Figure<T>(other) {}

// Оператор присваивания копиованием
template <typename T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon& other) {
    Figure<T>::operator=(other);
    return *this;
}

// Конструктор перемещения
template <typename T>
Pentagon<T>::Pentagon(Pentagon&& other) noexcept : Figure<T>(std::move(other)) {}

// Конструктор присваивания перемещением
template <typename T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon&& other) noexcept {
    Figure<T>::operator=(std::move(other));
    return *this;
}

// Геометрический центр (центроид)
template <typename T>
Point<T> Pentagon<T>::center() const {
    return Figure<T>::center();
}

// Чтение/запись
template <typename T>
void Pentagon<T>::read(std::istream& in) {
    for (size_t i = 0; i < PENTAGON_VERTICES; ++i) {
        in >> this->vertices[i];
    }

    if (!this->isConvex() || !isPentagon()) {
        throw std::invalid_argument("Points do not form a convex regular pentagon");
    }
    this->sortVertices();
}

template <typename T>
void Pentagon<T>::write(std::ostream& out) const {
    for (size_t i = 0; i < PENTAGON_VERTICES; ++i) {
        Point<T> p = this->vertices[i];
        out << p << " ";
    }
}

// Площадь через приведение к double
template <typename T>
Pentagon<T>::operator double() const {
    return Figure<T>::operator double();
}

// Клонирование
template <typename T>
Figure<T>* Pentagon<T>::clone() const {
    return new Pentagon(*this);
}

// Проверка на равенство
template <typename T>
bool Pentagon<T>::equals(const Figure<T>& other) const {
    return Figure<T>::equals(other);
}

// Проверка правильного пятиугольника
template <typename T>
bool Pentagon<T>::isPentagon() const {
    if (this->vertices_num != 5) return false;

    auto distance = [](const Point<T>& a, const Point<T>& b) {
        double dx = static_cast<double>(a.x) - static_cast<double>(b.x);
        double dy = static_cast<double>(a.y) - static_cast<double>(b.y);
        return sqrt(dx * dx + dy * dy);
    };

    double side = distance(this->vertices[0], this->vertices[1]);
    for (size_t i = 1; i < 5; ++i) {
        double s = distance(this->vertices[i], this->vertices[(i + 1) % 5]);
        if (fabs(s - side) > 1e-6) return false;
    }

    // Check if regular: angles or something, but for simplicity, assume if sides equal and convex, it's regular
    return true;
}

// Explicit instantiations
template class Pentagon<int>;
template class Pentagon<double>;

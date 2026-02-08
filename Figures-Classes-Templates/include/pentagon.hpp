#pragma once

#include <iostream>
#include <memory>
#include "point.hpp"
#include "figure.hpp"

template <typename T>
class Pentagon : public Figure<T> {
public:
    // Конструкторы
    Pentagon();

    Pentagon(std::unique_ptr<Point<T>[]> verts);

    // Конструктор копирования
    Pentagon(const Pentagon& other);

    // Оператор присваивания копиованием
    Pentagon& operator=(const Pentagon& other);

    // Конструктор перемещения
    Pentagon(Pentagon&& other) noexcept;

    // Конструктор присваивания перемещением
    Pentagon& operator=(Pentagon&& other) noexcept;

    // Деструктор
    virtual ~Pentagon() = default;

    // Геометрический центр (центроид)
    virtual Point<T> center() const override;

    // Чтение/запись
    virtual void read(std::istream& in) override;
    virtual void write(std::ostream& out) const override;

    // Тип фигуры
    virtual std::string type() const override { return "pentagon"; }

    // Проверка на то, что точки образуют правильный пятиугольник
    virtual bool isPentagon() const;

    // Клонирование
    virtual Figure<T>* clone() const override;

    // Площадь через приведение к double
    virtual operator double() const override;

    // Проверка на равенство
    virtual bool equals(const Figure<T>& other) const override;

protected:
    static constexpr size_t PENTAGON_VERTICES = 5;
};

// Реализации

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

template <typename T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon& other) {
    Figure<T>::operator=(other);
    return *this;
}

template <typename T>
Pentagon<T>::Pentagon(Pentagon&& other) noexcept : Figure<T>(std::move(other)) {}

template <typename T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon&& other) noexcept {
    Figure<T>::operator=(std::move(other));
    return *this;
}

template <typename T>
Point<T> Pentagon<T>::center() const {
    return Figure<T>::center();
}

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

template <typename T>
Pentagon<T>::operator double() const {
    return Figure<T>::operator double();
}

template <typename T>
Figure<T>* Pentagon<T>::clone() const {
    return new Pentagon(*this);
}

template <typename T>
bool Pentagon<T>::equals(const Figure<T>& other) const {
    return Figure<T>::equals(other);
}

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
        if (fabs(s - side) > 1e-3) return false;
    }
    return true;
}

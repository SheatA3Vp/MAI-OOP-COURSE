#pragma once

#include <iostream>
#include <memory>
#include "point.hpp"
#include "figure.hpp"

template <typename T>
class Trapezoid : public Figure<T> {
public:
    // Конструкторы
    Trapezoid();

    Trapezoid(std::unique_ptr<Point<T>[]> verts);

    // Конструктор копирования
    Trapezoid(const Trapezoid& other);

    // Оператор присваивания копиованием
    Trapezoid& operator=(const Trapezoid& other);

    // Конструктор перемещения
    Trapezoid(Trapezoid&& other) noexcept;

    // Конструктор присваивания перемещением
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    // Деструктор
    virtual ~Trapezoid() = default;

    // Геометрический центр (центроид)
    virtual Point<T> center() const override;

    // Чтение/запись
    virtual void read(std::istream& in) override;
    virtual void write(std::ostream& out) const override;

    // Тип фигуры
    virtual std::string type() const override { return "trapezoid"; }

    // Проверка на то, что точки образуют трапецию вписанную в круг
    virtual bool isTrapezoid() const;

    // Клонирование
    virtual Figure<T>* clone() const override;

    // Площадь через приведение к double
    virtual operator double() const override;

    // Проверка на равенство
    virtual bool equals(const Figure<T>& other) const override;

protected:
    static constexpr size_t TRAPEZOID_VERTICES = 4;
};

// Реализации

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

// Оператор присваивания копированием
template <typename T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other) {
    Figure<T>::operator=(other);
    return *this;
}

template <typename T>
Trapezoid<T>::Trapezoid(Trapezoid&& other) noexcept : Figure<T>(std::move(other)) {}

template <typename T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid&& other) noexcept {
    Figure<T>::operator=(std::move(other));
    return *this;
}

template <typename T>
Point<T> Trapezoid<T>::center() const {
    return Figure<T>::center();
}

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

template <typename T>
Trapezoid<T>::operator double() const {
    return Figure<T>::operator double();
}

template <typename T>
Figure<T>* Trapezoid<T>::clone() const {
    return new Trapezoid(*this);
}

template <typename T>
bool Trapezoid<T>::equals(const Figure<T>& other) const {
    return Figure<T>::equals(other);
}

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
    return fabs((side1 + side3) - (side2 + side4)) < 1.0;
}

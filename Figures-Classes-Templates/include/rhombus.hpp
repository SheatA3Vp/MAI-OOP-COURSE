#pragma once

#include <iostream>
#include <memory>
#include "point.hpp"
#include "figure.hpp"

template <typename T>
class Rhombus : public Figure<T> {
public:
    // Конструкторы
    Rhombus();

    Rhombus(std::unique_ptr<Point<T>[]> verts);

    // Конструктор копирования
    Rhombus(const Rhombus& other);

    // Оператор присваивания копиованием
    Rhombus& operator=(const Rhombus& other);

    // Конструктор перемещения
    Rhombus(Rhombus&& other) noexcept;

    // Конструктор присваивания перемещением
    Rhombus& operator=(Rhombus&& other) noexcept;

    // Деструктор
    virtual ~Rhombus() = default;

    // Геометрический центр (центроид)
    virtual Point<T> center() const override;

    // Чтение/запись
    virtual void read(std::istream& in) override;
    virtual void write(std::ostream& out) const override;

    // Тип фигуры
    virtual std::string type() const override { return "rhombus"; }

    // Проверка на то, что точки образуют ромб
    virtual bool isRhombus() const;

    // Клонирование
    virtual Figure<T>* clone() const override;

    // Площадь через приведение к double
    virtual operator double() const override;

    // Проверка на равенство
    virtual bool equals(const Figure<T>& other) const override;

protected:
    static constexpr size_t RHOMBUS_VERTICES = 4;
};

// Реализации

template <typename T>
Rhombus<T>::Rhombus() : Figure<T>(RHOMBUS_VERTICES) {}

template <typename T>
Rhombus<T>::Rhombus(std::unique_ptr<Point<T>[]> verts) : Figure<T>(RHOMBUS_VERTICES, std::move(verts)) {
    if (!isRhombus()) {
        throw std::invalid_argument("Points do not form a rhombus");
    }
    this->sortVertices();
}

// Конструктор копирования
template <typename T>
Rhombus<T>::Rhombus(const Rhombus& other) : Figure<T>(other) {}

template <typename T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus& other) {
    Figure<T>::operator=(other);
    return *this;
}

template <typename T>
Rhombus<T>::Rhombus(Rhombus&& other) noexcept : Figure<T>(std::move(other)) {}

template <typename T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus&& other) noexcept {
    Figure<T>::operator=(std::move(other));
    return *this;
}

template <typename T>
Point<T> Rhombus<T>::center() const {
    return Figure<T>::center();
}

template <typename T>
void Rhombus<T>::read(std::istream& in) {
    for (size_t i = 0; i < RHOMBUS_VERTICES; ++i) {
        in >> this->vertices[i];
    }
    if (!this->isConvex() || !isRhombus()) {
        throw std::invalid_argument("Points do not form a convex rhombus");
    }
    this->sortVertices();
}

template <typename T>
void Rhombus<T>::write(std::ostream& out) const {
    for (size_t i = 0; i < RHOMBUS_VERTICES; ++i) {
        Point<T> p = this->vertices[i];
        out << p << " ";
    }
}

template <typename T>
Rhombus<T>::operator double() const {
    return Figure<T>::operator double();
}

template <typename T>
Figure<T>* Rhombus<T>::clone() const {
    return new Rhombus(*this);
}

template <typename T>
bool Rhombus<T>::equals(const Figure<T>& other) const {
    return Figure<T>::equals(other);
}

template <typename T>
bool Rhombus<T>::isRhombus() const {
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
    return fabs(side1 - side2) < 1e-6 && fabs(side2 - side3) < 1e-6 && fabs(side3 - side4) < 1e-6;
}

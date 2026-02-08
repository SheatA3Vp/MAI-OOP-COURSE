#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "point.hpp"


template <typename T>
class Figure {
public:

    // Конструкторы
    Figure();

    Figure(size_t n);

    Figure(size_t n, std::unique_ptr<Point<T>[]> verts);

    // Конструктор копирования
    Figure(const Figure& other);

    // Оператор присваивания копированием
    Figure& operator=(const Figure& other);

    // Конструктор перемещения
    Figure(Figure&& other) noexcept;

    // Оператор присваивания перемещением
    Figure& operator=(Figure&& other) noexcept;

    // Деструктор
    virtual ~Figure();

    // Геометрический центр (центроид)
    virtual Point<T> center() const;

    // Проверка на выпуклость
    virtual bool isConvex() const;

    // Сортировка вершин по порядку обхода
    virtual void sortVertices();

    // Чтение/запись
    virtual void read(std::istream& in);
    virtual void write(std::ostream& out) const;

    // Тип фигуры
    virtual std::string type() const = 0;

    // Клонирование
    virtual Figure* clone() const = 0;

    // Площадь через приведение к double
    virtual operator double() const;

    // Проверка на равенство
    virtual bool equals(const Figure& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Figure& f) {
        f.write(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Figure& f) {
        f.read(in);
        return in;
    }

protected:
    size_t vertices_num;
    std::unique_ptr<Point<T>[]> vertices;
};

// Implementations

// Конструкторы
template <typename T>
Figure<T>::Figure() : Figure(1) {}

template <typename T>
Figure<T>::Figure(size_t n) : vertices_num(n) {
    this->vertices = std::make_unique<Point<T>[]>(n);

    for (size_t i = 0; i < n; ++i) {
        this->vertices[i] = Point<T>();
    }
}

template <typename T>
Figure<T>::Figure(size_t n, std::unique_ptr<Point<T>[]> verts) : vertices_num(n), vertices(std::move(verts)) {
    if (!isConvex()) {
        throw std::invalid_argument("Figure is not convex");
    }
}

// Конструктор копирования
template <typename T>
Figure<T>::Figure(const Figure& other) : vertices_num(other.vertices_num) {
    this->vertices = std::make_unique<Point<T>[]>(vertices_num);
    for (size_t i = 0; i < vertices_num; ++i) {
        this->vertices[i] = other.vertices[i];
    }
}

// Оператор присваивания копированием
template <typename T>
Figure<T>& Figure<T>::operator=(const Figure& other) {
    if (this != &other) {
        this->vertices_num = other.vertices_num;
        this->vertices = std::make_unique<Point<T>[]>(vertices_num);
        for (size_t i = 0; i < this->vertices_num; ++i) {
            this->vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

// Конструктор перемещения
template <typename T>
Figure<T>::Figure(Figure&& other) noexcept : vertices_num(other.vertices_num), vertices(std::move(other.vertices)) {
    other.vertices_num = 0;
}

// Оператор присваивания перемещением
template <typename T>
Figure<T>& Figure<T>::operator=(Figure&& other) noexcept {
    if (this != &other) {
        this->vertices = std::move(other.vertices);
        this->vertices_num = other.vertices_num;
        other.vertices_num = 0;
    }
    return *this;
}

// Деструктор
template <typename T>
Figure<T>::~Figure() {}

// Чтение и запись
template <typename T>
void Figure<T>::read(std::istream& in) {
    size_t n;
    in >> n;
    this->vertices_num = n;
    this->vertices = std::make_unique<Point<T>[]>(n);
    for (size_t i = 0; i < n; ++i) {
        in >> this->vertices[i];
    }
    if (!isConvex()) {
        throw std::invalid_argument("Figure is not convex");
    }
}

template <typename T>
void Figure<T>::write(std::ostream& out) const {
    for (size_t i = 0; i < this->vertices_num; ++i) {
        Point<T> p = this->vertices[i];
        out << p << " ";
    }
}

// Проверка на равенство
template <typename T>
bool Figure<T>::equals(const Figure& other) const {
    if (!(this->vertices_num == other.vertices_num)) return false;
    for (size_t i = 0; i < this->vertices_num; ++i) {
        if (this->vertices[i] != other.vertices[i]) return false;
    }
    return true;
}

// Нахождение центроида
template <typename T>
Point<T> Figure<T>::center() const {
    Point<T> center;
    for (size_t i = 0; i < this->vertices_num; ++i) {
        center = center + this->vertices[i];
    }
    return center / this->vertices_num;
}

// Сортировка вершин по порядку обхода
template <typename T>
void Figure<T>::sortVertices() {
    Point<T> c = center();
    std::sort(vertices.get(), vertices.get() + vertices_num, [&](const Point<T>& a, const Point<T>& b) {
        double angleA = atan2(static_cast<double>(a.y) - static_cast<double>(c.y), static_cast<double>(a.x) - static_cast<double>(c.x));
        double angleB = atan2(static_cast<double>(b.y) - static_cast<double>(c.y), static_cast<double>(b.x) - static_cast<double>(c.x));
        return angleA < angleB;
    });
}

// Нахождение площади с помощью метода шнурков
template <typename T>
Figure<T>::operator double() const {
    double S = 0;
    double sum1 = 0;
    double sum2 = 0;
    for (size_t i = 0; i < this->vertices_num - 1; ++i) {
        sum1 += static_cast<double>(this->vertices[i].x) * static_cast<double>(this->vertices[i + 1].y);
        sum2 += static_cast<double>(this->vertices[i].y) * static_cast<double>(this->vertices[i + 1].x);
    }
    sum1 += static_cast<double>(this->vertices[vertices_num - 1].x) * static_cast<double>(this->vertices[0].y);
    sum2 += static_cast<double>(this->vertices[vertices_num - 1].y) * static_cast<double>(this->vertices[0].x);
    S = 0.5 * fabs(sum1 - sum2);
    return S;
}

// Проверка на выпуклость
template <typename T>
bool Figure<T>::isConvex() const {
    if (vertices_num < 3) return true;
    int sign = 0;
    for (size_t i = 0; i < vertices_num; ++i) {
        Point<T> a = vertices[i];
        Point<T> b = vertices[(i + 1) % vertices_num];
        Point<T> c = vertices[(i + 2) % vertices_num];
        double cross = (static_cast<double>(b.x) - static_cast<double>(a.x)) * (static_cast<double>(c.y) - static_cast<double>(a.y)) - (static_cast<double>(b.y) - static_cast<double>(a.y)) * (static_cast<double>(c.x) - static_cast<double>(a.x));
        if (cross == 0) continue; // коллинеарные точки, пропускаем
        int current_sign = (cross > 0) ? 1 : -1;
        if (sign == 0) sign = current_sign;
        else if (sign != current_sign) return false;
    }
    return true;
}

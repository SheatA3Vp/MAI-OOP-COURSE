#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include <stdexcept>
#include "point.hpp"


class Figure {
public:

    // Конструкторы
    Figure();

    Figure(size_t n);

    Figure(size_t n, Point* verts);

    // Конструктор копирования
    Figure(const Figure& other);

    // Оператор присваивания копированием
    Figure& operator=(const Figure& other);

    // Конструктор перемещения
    Figure(Figure&& other) noexcept;

    // Конструктор присваивания перемещением
    Figure& operator=(Figure&& other) noexcept;

    // Деструктор
    virtual ~Figure();

    // Геометрический центр (центроид)
    virtual Point center() const;

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
    Point* vertices;
};
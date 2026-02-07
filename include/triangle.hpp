#pragma once

#include <iostream>
#include <memory>
#include "point.hpp"
#include "figure.hpp"

class Triangle : public Figure {
public:
    // Конструкторы
    Triangle();

    Triangle(Point* verts);

    // Конструктор копирования
    Triangle(const Triangle& other);

    // Оператор присваивания копированием
    Triangle& operator=(const Triangle& other);

    // Конструктор перемещения
    Triangle(Triangle&& other) noexcept;

    // Конструктор присваивания перемещением
    Triangle& operator=(Triangle&& other) noexcept;

    // Деструктор
    virtual ~Triangle() = default;

    // Геометрический центр (центроид)
    virtual Point center() const override;

    // Чтение/запись
    virtual void read(std::istream& in) override;
    virtual void write(std::ostream& out) const override;

    // Тип фигуры
    virtual std::string type() const override { return "triangle"; }

    // Клонирование
    virtual Figure* clone() const override;

    // Площадь через приведение к double
    virtual operator double() const override;

    // Проверка на равенство
    virtual bool equals(const Figure& other) const override;

protected:
    static constexpr size_t TRIANGLE_VERTICES = 3;
};
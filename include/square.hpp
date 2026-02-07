#pragma once

#include <iostream>
#include <memory>
#include "point.hpp"
#include "figure.hpp"

class Square : public Figure {
public:
    // Конструкторы
    Square();

    Square(Point* verts);

    // Конструктор копирования
    Square(const Square& other);

    // Оператор присваивания копированием
    Square& operator=(const Square& other);

    // Конструктор перемещения
    Square(Square&& other) noexcept;

    // Конструктор присваивания перемещением
    Square& operator=(Square&& other) noexcept;

    // Деструктор
    virtual ~Square() = default;

    // Геометрический центр (центроид)
    virtual Point center() const override;

    // Чтение/запись
    virtual void read(std::istream& in) override;
    virtual void write(std::ostream& out) const override;

    // Тип фигуры
    virtual std::string type() const override { return "square"; }

    // Проверка на то, что точки образуют квадрат
    virtual bool isSquare() const;

    // Клонирование
    virtual Figure* clone() const override;

    // Площадь через приведение к double
    virtual operator double() const override;

    // Проверка на равенство
    virtual bool equals(const Figure& other) const override;

protected:
    static constexpr size_t SQUARE_VERTICES = 4;
};
#pragma once

#include <iostream>
#include <concepts>

template <typename T>
concept Number = (std::integral<T> || std::floating_point<T>) 
                 && !std::same_as<T, bool>
                 && !std::same_as<T, char>;

template <typename T> requires Number<T>
struct Point {
    double x = 0.0;
    double y = 0.0;

    bool operator==(const Point& other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    Point operator+(const Point& other) {
        Point p;
        p.x = this->x + other.x;
        p.y = this->y + other.y;
        return p;
    }

    Point operator-(const Point& other) const {
        Point p;
        p.x = this->x - other.x;
        p.y = this->y - other.y;
        return p;
    }

    Point operator/(const size_t n) {
        Point p;
        double n_dbl = static_cast<double>(n);
        p.x = this->x / n_dbl;
        p.y = this->y / n_dbl;
        return p;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        out << '(' << p.x << ", " << p.y << ')';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Point& p) {
        in >> std::ws; // Пропускаем пробелы
        if (!in)
            return in;

        if (!(in >> p.x >> p.y)) {
            in.setstate(std::ios::failbit);
            return in;
        }

        return in;
    }
};
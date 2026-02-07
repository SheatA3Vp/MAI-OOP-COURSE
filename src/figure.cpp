#include "../include/figure.hpp"
#include <algorithm>

// Конструкторы
Figure::Figure() : Figure(1) {}

Figure::Figure(size_t n) : vertices_num(n) {
    this->vertices = new Point[n];

    for (size_t i = 0; i < n; ++i) {
        this->vertices[i] = Point();
    }
}

Figure::Figure(size_t n, Point* verts) : vertices_num(n) {
    this->vertices = new Point[n];

    if (verts != nullptr) {
        for (size_t i = 0; i < n; ++i) {
            this->vertices[i] = verts[i];
        }        
    } else {
        for (size_t i = 0; i < n; ++i) {
            this->vertices[i] = Point();
        }
    }

    if (!isConvex()) {
        throw std::invalid_argument("Figure is not convex");
    }
}

// Конструктор копирования
Figure::Figure(const Figure& other) : vertices_num(other.vertices_num) {
    size_t n = other.vertices_num;
    this->vertices = new Point[n];

    for (size_t i = 0; i < n; ++i) {
        this->vertices[i] = other.vertices[i];
    }
}

// Оператор присваивания копированием
Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        delete[] this->vertices;
        this->vertices_num = other.vertices_num;
        this->vertices = new Point[other.vertices_num];

        for (size_t i = 0; i < this->vertices_num; ++i) {
            this->vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

// Конструктор перемещения
Figure::Figure(Figure&& other) noexcept : vertices_num(other.vertices_num), vertices(other.vertices) {
    other.vertices_num = 0;
    other.vertices = nullptr;
}

// Оператор присваивания перемещением
Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        delete[] this->vertices;
        this->vertices = other.vertices;
        this->vertices_num = other.vertices_num;
        other.vertices = nullptr;
        other.vertices_num = 0;
    }

    return *this;
}

// Деструктор
Figure::~Figure() {
    delete[] this->vertices;
}

// Чтение и запись
void Figure::read(std::istream& in) {
    size_t n;
    in >> n;
    this->vertices_num = n;

    for (size_t i = 0; i < n; ++i) {
        in >> this->vertices[i];
    }

    if (!isConvex()) {
        throw std::invalid_argument("Figure is not convex");
    }
}

void Figure::write(std::ostream& out) const {
    for (size_t i = 0; i < this->vertices_num; ++i) {
        Point p = this->vertices[i];
        out << p << " ";
    }
}

// Проверка на равенство
bool Figure::equals(const Figure& other) const {
    if (!(this->vertices_num == other.vertices_num)) return false;

    for (size_t i = 0; i < this->vertices_num; ++i) {
        if (this->vertices[i] != other.vertices[i]) return false;
    }

    return true;
}

// Нахождение центроида
Point Figure::center() const {
    Point center;
    for (size_t i = 0; i < this->vertices_num; ++i) {
        center = center + this->vertices[i];
    }
    return center / this->vertices_num;
}

// Сортировка вершин по порядку обхода
void Figure::sortVertices() {
    Point c = center();
    std::sort(vertices, vertices + vertices_num, [&](const Point& a, const Point& b) {
        double angleA = atan2(a.y - c.y, a.x - c.x);
        double angleB = atan2(b.y - c.y, b.x - c.x);
        return angleA < angleB;
    });
}

// Нахождение площади с помощью метода шнурков
Figure::operator double() const {
    double S = 0;
    double sum1 = 0;
    double sum2 = 0;

    for (size_t i = 0; i < this->vertices_num - 1; ++i) {
        sum1 += this->vertices[i].x * this->vertices[i + 1].y;
        sum2 += this->vertices[i].y * this->vertices[i + 1].x;
    }

    sum1 += this->vertices[vertices_num - 1].x * this->vertices[0].y;
    sum2 += this->vertices[vertices_num - 1].y * this->vertices[0].x;

    S = 0.5 * fabs(sum1 - sum2);

    return S;
}

// Проверка на выпуклость
bool Figure::isConvex() const {
    if (vertices_num < 3) return true;

    int sign = 0;
    for (size_t i = 0; i < vertices_num; ++i) {
        Point a = vertices[i];
        Point b = vertices[(i + 1) % vertices_num];
        Point c = vertices[(i + 2) % vertices_num];

        double cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

        if (cross == 0) continue; // коллинеарные точки, пропускаем

        int current_sign = (cross > 0) ? 1 : -1;

        if (sign == 0) sign = current_sign;
        else if (sign != current_sign) return false;
    }

    return true;
}
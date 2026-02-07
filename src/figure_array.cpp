#include "../include/figure_array.hpp"

// Конструкторы
FigureArray::FigureArray() : FigureArray(0) {}

FigureArray::FigureArray(size_t n) {
    this->capacity = 10;
    if (n < 1) {
        // error 
    }
    while (n > capacity) capacity *= 2;
    this->array = new Figure*[capacity];
    this->size = 0;
}

// Конструктор копирования
FigureArray::FigureArray(const FigureArray& other) : size(other.size), capacity(other.capacity) {
    if (this->size > 0) {
        this->array = new Figure*[capacity];
        for (size_t i = 0; i < this->size; ++i) {
            this->array[i] = other.array[i]->clone();
        }
    } else {
        this->array = nullptr;
    }
}

// Оператор присваивания копиованием
FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this->capacity > 0) {
        for (size_t i = 0; i < this->size; ++i) {
            delete this->array[i];
        }
        delete[] this->array;
    }
    this->size = other.size;
    this->capacity = other.capacity;
    this->array = new Figure*[this->capacity];
    for (size_t i = 0; i < other.size; ++i) {
        this->array[i] = other.array[i]->clone();
    }
    return *this;
}

// Конструктор перемещения
FigureArray::FigureArray(FigureArray&& other) noexcept : size(other.size), capacity(other.capacity), array(other.array) {
    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;    
}

// Конструктор присваивания перемещением
FigureArray& FigureArray::operator=(FigureArray&& other) noexcept {
    if (this->capacity > 0) {
        for (size_t i = 0; i < this->size; ++i) {
            delete this->array[i];
        }
        delete[] this->array;
    }
    this->size = other.size;
    this->capacity = other.capacity;
    this->array = other.array;
    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;
    return *this;
}

// Деструктор
FigureArray::~FigureArray() {
    if (this->capacity > 0) {
        for (size_t i = 0; i < this->size; ++i) {
            delete this->array[i];
        }
        delete[] this->array;
    } else {
        this->array = nullptr;
    }
    this->size = 0;
    this->capacity = 0;
}

// Изменение размера
void FigureArray::resize(const size_t new_capacity) {
    if (new_capacity <= this->capacity) return;
    size_t new_cap = this->capacity;
    while (new_cap < new_capacity) new_cap *= 2;
    Figure** new_array = new Figure*[new_cap];
    for (size_t i = 0; i < this->size; ++i) {
        new_array[i] = this->array[i];
    }
    delete[] this->array;
    this->array = new_array;
    this->capacity = new_cap;
}

// Добавление элемента в массив
void FigureArray::add(Figure& f) {
    if (this->size + 1 > capacity) {
        this->resize(this->size + 1);
    }

    this->array[this->size] = &f;
    ++this->size;
}

// Удаление по индексу
void FigureArray::pop(size_t index) {
    delete this->array[index];
    for (size_t i = index + 1; i < this->size; ++i) {
        this->array[i - 1] = this->array[i];
    }
    --this->size;
    this->array[this->size] = nullptr;
}

// Печатаем геометрический центр (центроид) всех фигур
void FigureArray::array_center() const {
    for (size_t i = 0; i < this->size; ++i) {
        std::cout << this->array[i]->center() <<std::endl;
    }
}

// Печатаем площадь всех фигур
void FigureArray::array_square() const {
    for (size_t i = 0; i < this->size; ++i) {
        std::cout << static_cast<double>(*(this->array[i])) <<std::endl;
    }
}

// Общая площадь всех фигур
double FigureArray::total_area() const {
    double sum = 0.0;
    for (size_t i = 0; i < this->size; ++i) {
        sum += static_cast<double>(*(this->array[i]));
    }
    return sum;
}

// Чтение/запись
void FigureArray::read(std::istream& in) {
    std::string type;
    while (in >> type) {
        Figure* f = nullptr;
        try {
            if (type == "triangle") {
                f = new Triangle();
            } else if (type == "square") {
                f = new Square();
            } else if (type == "octagon") {
                f = new Octagon();
            } else {
                // unknown type, skip
                continue;
            }
            f->read(in);
            this->add(*f);
        } catch (...) {
            delete f;
            throw;
        }
    }
}

void FigureArray::write(std::ostream& out) const {
    for (size_t i = 0; i < this->size; ++i) {
        out << this->array[i]->type() << " " << *(this->array[i]) << std::endl;
    }
}
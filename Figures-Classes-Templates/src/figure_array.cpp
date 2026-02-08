#include "../include/figure_array.hpp"

// Конструкторы
template <typename T>
Array<T>::Array() : Array(0) {}

template <typename T>
Array<T>::Array(size_t n) {
    this->capacity = 10;
    if (n > 0) {
        while (n > capacity) capacity *= 2;
    }
    this->array = std::make_shared<T[]>(capacity);
    this->size = 0;
}

// Конструктор копирования
template <typename T>
Array<T>::Array(const Array& other) : size(other.size), capacity(other.capacity) {
    if (this->size > 0) {
        this->array = std::make_shared<T[]>(capacity);
        for (size_t i = 0; i < this->size; ++i) {
            if constexpr (std::is_pointer_v<T>) {
                this->array[i] = static_cast<T>(other.array[i]->clone());
            } else {
                this->array[i] = other.array[i];
            }
        }
    }
}

// Оператор присваивания копированием
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this->capacity > 0) {
        if constexpr (std::is_pointer_v<T>) {
            for (size_t i = 0; i < this->size; ++i) {
                delete this->array[i];
            }
        }
    }
    this->size = other.size;
    this->capacity = other.capacity;
    this->array = std::make_shared<T[]>(this->capacity);
    for (size_t i = 0; i < other.size; ++i) {
        if constexpr (std::is_pointer_v<T>) {
            this->array[i] = static_cast<T>(other.array[i]->clone());
        } else {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}

// Конструктор перемещения
template <typename T>
Array<T>::Array(Array&& other) noexcept : size(other.size), capacity(other.capacity), array(other.array) {
    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;    
}

// Конструктор присваивания перемещением
template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this->capacity > 0) {
        if constexpr (std::is_pointer_v<T>) {
            for (size_t i = 0; i < this->size; ++i) {
                delete this->array[i];
            }
        }
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
template <typename T>
Array<T>::~Array() {
    if (this->capacity > 0) {
        if constexpr (std::is_pointer_v<T>) {
            for (size_t i = 0; i < this->size; ++i) {
                delete this->array[i];
            }
        }
    }
}

// Изменение размера
template <typename T>
void Array<T>::resize(const size_t new_capacity) {
    if (new_capacity <= this->capacity) return;
    size_t new_cap = this->capacity;
    while (new_cap < new_capacity) new_cap *= 2;
    auto new_array = std::make_shared<T[]>(new_cap);
    for (size_t i = 0; i < this->size; ++i) {
        if constexpr (std::is_pointer_v<T>) {
            new_array[i] = this->array[i];
        } else {
            new_array[i] = std::move(this->array[i]);
        }
    }
    this->array = new_array;
    this->capacity = new_cap;
}

// Добавление элемента в массив
template <typename T>
void Array<T>::add(T f) {
    if (this->size + 1 > capacity) {
        this->resize(this->size + 1);
    }
    if constexpr (std::is_pointer_v<T>) {
        this->array[this->size] = f;
    } else {
        this->array[this->size] = std::move(f);
    }
    ++this->size;
}

// Удаление по индексу
template <typename T>
void Array<T>::pop(size_t index) {
    if constexpr (std::is_pointer_v<T>) {
        delete this->array[index];
    }
    for (size_t i = index + 1; i < this->size; ++i) {
        this->array[i - 1] = this->array[i];
    }
    --this->size;
    this->array[this->size] = T{};
}

// Печатаем геометрический центр (центроид) всех фигур
template <typename T>
void Array<T>::array_center() const {
    for (size_t i = 0; i < this->size; ++i) {
        if constexpr (std::is_pointer_v<T>) {
            std::cout << this->array[i]->center() << std::endl;
        } else {
            std::cout << this->array[i].center() << std::endl;
        }
    }
}

// Печатаем площадь всех фигур
template <typename T>
void Array<T>::array_square() const {
    for (size_t i = 0; i < this->size; ++i) {
        if constexpr (std::is_pointer_v<T>) {
            std::cout << static_cast<double>(*(this->array[i])) << std::endl;
        } else {
            std::cout << static_cast<double>(this->array[i]) << std::endl;
        }
    }
}

// Общая площадь всех фигур
template <typename T>
double Array<T>::total_area() const {
    double sum = 0.0;
    for (size_t i = 0; i < this->size; ++i) {
        if constexpr (std::is_pointer_v<T>) {
            sum += static_cast<double>(*(this->array[i]));
        } else {
            sum += static_cast<double>(this->array[i]);
        }
    }
    return sum;
}

// Чтение/запись
template <typename T>
void Array<T>::read(std::istream& in) {
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

template <typename T>
void Array<T>::write(std::ostream& out) const {
    for (size_t i = 0; i < this->size; ++i) {
        if constexpr (std::is_pointer_v<T>) {
            out << this->array[i]->type() << " " << *(this->array[i]) << std::endl;
        } else {
            out << this->array[i].type() << " " << this->array[i] << std::endl;
        }
    }
}
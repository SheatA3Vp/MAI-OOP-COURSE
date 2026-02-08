#include "figure.hpp"
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include <type_traits>

template <typename T>
class Array
{
public:
    // Конструкторы
    Array();

    Array(size_t n);

    // Конструктор копирования
    Array(const Array& other);

    // Оператор присваивания копиованием
    Array& operator=(const Array& other);

    // Конструктор перемещения
    Array(Array&& other) noexcept;

    // Конструктор присваивания перемещением
    Array& operator=(Array&& other) noexcept;

    // Деструктор
    virtual ~Array();

    // Изменение размера
    virtual void resize(const size_t new_size); 

    // Добавление элемента в массив
    virtual void add(T f);

    // Удаление по индексу
    virtual void pop(size_t index);

    // Печатаем геометрический центр (центроид) всех фигур
    virtual void array_center() const;

    // Печатаем площадь всех фигур
    virtual void array_square() const;

    // Общая площадь всех фигур
    virtual double total_area() const;

    // Получить размер
    size_t get_size() const { return size; }

    // Чтение/запись
    virtual void read(std::istream& in);
    virtual void write(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const Array& f) {
        f.write(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Array& f) {
        f.read(in);
        return in;
    }
private:
    size_t size;
    size_t capacity;
    std::shared_ptr<T[]> array;
};

// Implementations

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

template <typename T>
Array<T>::Array(Array&& other) noexcept : size(other.size), capacity(other.capacity), array(other.array) {
    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;    
}

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

template <typename T>
void Array<T>::read(std::istream& in) {
    // Not implemented
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
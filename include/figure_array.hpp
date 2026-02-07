#include "figure.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"

class FigureArray 
{
public:
    // Конструкторы
    FigureArray();

    FigureArray(size_t n);

    // Конструктор копирования
    FigureArray(const FigureArray& other);

    // Оператор присваивания копированием
    FigureArray& operator=(const FigureArray& other);

    // Конструктор перемещения
    FigureArray(FigureArray&& other) noexcept;

    // Конструктор присваивания перемещением
    FigureArray& operator=(FigureArray&& other) noexcept;

    // Деструктор
    virtual ~FigureArray();

    // Изменение размера
    virtual void resize(const size_t new_size); 

    // Добавление элемента в массив
    virtual void add(Figure& f);

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

    friend std::ostream& operator<<(std::ostream& out, const FigureArray& f) {
        f.write(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, FigureArray& f) {
        f.read(in);
        return in;
    }
private:
    size_t size;
    size_t capacity;
    Figure** array;
};
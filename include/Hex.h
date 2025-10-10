#pragma once

#include <string>
#include <iostream>


class Hex {
public:
    // === КОНСТРУКТОРЫ ===
    
    // Конструктор по умолчанию
    Hex();
    
    // Конструктор из списка инициализации (C++11)
    Hex(const std::initializer_list<unsigned char>& initialValues);
    
    // Конструктор из строки
    Hex(const std::string& sourceString);
    
    // === КОПИРУЮЩИЕ И ПЕРЕМЕЩАЮЩИЕ ОПЕРАЦИИ ===
    
    // Копирующий конструктор
    Hex(const Hex& other);
    
    // Перемещающий конструктор (C++11)
    Hex(Hex&& other) noexcept;

    // === ОПЕРАЦИИ С МАССИВАМИ ===
    
    // Сложение чисел
    Hex addition(const Hex& other);
    
    // Вычитание чисел
    Hex subtraction(const Hex& other);
    
    // Сравнение чисел на равенство
    bool equals(const Hex& other) const;

    // Сравнение чисел (знак больше)
    bool greater(const Hex& other) const;

    // Сравнение чисел (знак меньше)
    bool less(const Hex& other) const;
    
    // Вывод массива в поток
    std::ostream& print(std::ostream& outputStream);

    // === ДЕСТРУКТОР ===
    
    // Виртуальный деструктор
    virtual ~Hex() noexcept;

private:
    // === ДАННЫЕ-ЧЛЕНЫ ===
    
    size_t numSize;           // Размер числа
    unsigned char* dataHex;   // Указатель на динамический массив с числом
};

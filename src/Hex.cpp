#include "Hex.h"

// === РЕАЛИЗАЦИЯ КОНСТРУКТОРОВ ===

// Конструктор по умолчанию
Hex::Hex() : numSize(0), dataHex(nullptr) {}

// Конструктор из списка инициализации (C++11)
// TODO: реверс
Hex::Hex(const std::initializer_list<unsigned char>& initialValues) {
    numSize = initialValues.size();
    dataHex = new unsigned char[numSize];

    // Копируем значения из списка инициализации
    size_t index = 0;
    for (const auto& value : initialValues) {
        dataHex[index++] = value;
    }
}

// Конструктор из строки
// TODO: реверс
Hex::Hex(const std::string& sourceString) {
    numSize = sourceString.size();
    dataHex = new unsigned char[numSize];
    
    // Копируем символы из строки
    for (size_t i = 0; i < numSize; ++i) {
        dataHex[i] = static_cast<unsigned char>(sourceString[i]);
    }
}

// Копирующий конструктор (глубокое копирование)
Hex::Hex(const Hex& other) {
    numSize = other.numSize;
    dataHex = new unsigned char[numSize];
    
    // Глубокое копирование данных
    for (size_t i = 0; i < numSize; ++i) {
        dataHex[i] = other.dataHex[i];
    }
}

// Перемещающий конструктор (C++11)
Hex::Hex(Hex&& other) noexcept {
    numSize = other.numSize;
    dataHex = other.dataHex;
    
    // Обнуляем другой объект, чтобы деструктор не освободил память
    other.numSize = 0;
    other.dataHex = nullptr;
}

// === РЕАЛИЗАЦИЯ ОПЕРАЦИЙ ===

// Сложение чисел (не реализовано)
Hex Hex::addition(const Hex& other) {

    return Hex(this->numSize + other.numSize);
}

// Вычитание чисел (не реализовано)
Hex Hex::subtraction(const Hex& other) {

    return *this;
}

// Сравнение чисел на равенство (не реализовано)
bool Hex::equals(const Hex& other) const {}

// Сравнение чисел (знак больше) (не реализовано)
bool Hex::greater(const Hex& other) const {}

// Сравнение чисел (знак меньше) (не реализовано)
bool Hex::less(const Hex& other) const {}

// Вывод массива в поток
std::ostream& Hex::print(std::ostream& outputStream) {
    for (size_t i = 0; i < numSize; ++i) {
        outputStream << dataHex[i];
    }
    return outputStream;
}

// === РЕАЛИЗАЦИЯ ДЕСТРУКТОРА ===

// Деструктор - освобождает динамическую память
Hex::~Hex() noexcept {
    std::cout << "Деструктор" << std::endl;
    
    // Освобождаем память, если она была выделена
    if (dataHex != nullptr) {
        delete[] dataHex;
        dataHex = nullptr;
    }
    
    // Обнуляем размер для безопасности
    numSize = 0;
}
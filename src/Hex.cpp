#include "../include/Hex.hpp"
#include <vector>
#include <bits/stdc++.h>

// === РЕАЛИЗАЦИЯ КОНСТРУКТОРОВ ===

// Конструктор по умолчанию
Hex::Hex() : numSize(0), dataHex(nullptr) {}

// Конструктор из списка инициализации (C++11)
Hex::Hex(const std::initializer_list<unsigned char>& initialValues) {
    numSize = initialValues.size();
    // Проверка на незначащие нули + на соответсвие цифрам 16-ричного алфавита
    int areInsignifZeros = 1;
    int InsignifZerosCounter = 0;
    for (const auto& value : initialValues) {
        int ch = static_cast<int> (value);
        if (ch == '0' && areInsignifZeros) {
            ++InsignifZerosCounter;
        } else {
            if ( !((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F')) ) {
                throw std::logic_error("Число должно быть в 16-ричной системе счисления и не иметь знаков.");
            }
            areInsignifZeros = 0;
        }
    }

    if (InsignifZerosCounter == numSize) {
        numSize = 1;
        dataHex = new unsigned char[numSize];
        dataHex[0] = '0';
    } else {
        numSize -= InsignifZerosCounter;
        dataHex = new unsigned char[numSize];

        size_t index = numSize - 1;
        for (const auto& value : initialValues) {
            if (InsignifZerosCounter) {
                --InsignifZerosCounter;
                continue;
            }
            dataHex[index--] = value;
        }
    }
}

// Конструктор из строки
Hex::Hex(const std::string& sourceString) {
    numSize = sourceString.size();
    size_t start = 0;
    while( static_cast<int>(sourceString[start]) == '0' && start + 1 != numSize) {
        ++start;
    }
    numSize -= start;
    if (numSize == 0) {
        numSize = 1;
        dataHex = new unsigned char[1];
        dataHex[0] = '0';
    } else {
        dataHex = new unsigned char[numSize];
        
        // Копируем символы из вектора
        for (size_t i = 0; i < numSize; ++i) {
            int ch = static_cast<int>(sourceString[i + start]);
            if ( !((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F')) ) {
                delete[] dataHex;
                throw std::logic_error("Число должно быть в 16-ричной системе счисления и не иметь знаков.");
            }
            dataHex[numSize - i - 1] = ch;
        }
    }
}

// Конструктор из вектора
Hex::Hex(const std::vector<unsigned char>& sourceVector) {
    numSize = sourceVector.size();
    size_t start = 0;
    while( static_cast<int>(sourceVector[start]) == '0' && start + 1 != numSize) {
        ++start;
    }
    numSize -= start;
    if (numSize == 0) {
        numSize = 1;
        dataHex = new unsigned char[1];
        dataHex[0] = '0';
    } else {
        dataHex = new unsigned char[numSize];
        
        // Копируем символы из вектора
        for (size_t i = 0; i < numSize; ++i) {
            int ch = static_cast<int>(sourceVector[i + start]);
            if ( !((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F')) ) {
                delete[] dataHex;
                throw std::logic_error("Число должно быть в 16-ричной системе счисления и не иметь знаков.");
            }
            dataHex[numSize - i - 1] = ch;
        }
    }
}

// Копирующий конструктор (глубокое копирование)
Hex::Hex(const Hex& other) {
    numSize = other.numSize;
    dataHex = new unsigned char[numSize];

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

// === РЕАЛИЗАЦИЯ ГЕТТЕРОВ ===

size_t Hex::getSize() const { return this->numSize; }

unsigned char Hex::getDigit(size_t index) const { return this->dataHex[index]; }

// === РЕАЛИЗАЦИЯ ОПЕРАЦИЙ ===

// Сложение чисел
Hex Hex::add(const Hex& other) {
    std::vector<unsigned char> result;
    size_t max_size = std::max(this->numSize, other.numSize);
    size_t i = 0;
    int k = 0;
    unsigned char ch;

    for (; i < max_size; ++i) {
        int num = 0;
        int cur = 0;
        int sum = k;
        if (i < this->numSize) {
            if (!isdigit(this->dataHex[i])) {
                cur = static_cast<int> (this->dataHex[i] - 'A' + 10);
            } else {
                cur = static_cast<int> (this->dataHex[i] - '0');
            }            
        } else {
            cur = 0;
        }
        sum += cur;

        if (i < other.numSize) {
            if (!isdigit(other.dataHex[i])) {
                cur = static_cast<int> (other.dataHex[i] - 'A' + 10);
            } else {
                cur = static_cast<int> (other.dataHex[i] - '0');
            }
        } else {
            cur = 0;
        }
        sum += cur;

        num = sum % 16;
        k = sum / 16;
        if (num > 9) {
            ch = static_cast<unsigned char> (num + 'A' - 10);
        } else {
            ch = static_cast<unsigned char> (num + '0');
        }

        result.push_back(ch);
    }

    if (k > 0) {
        if (k > 9) {
            ch = static_cast<unsigned char>(k + 'A' - 10);
        } else {
            ch = static_cast<unsigned char>(k + '0');
        }
        result.push_back(ch);
    }

    std::reverse(result.begin(), result.end());
    return Hex(result);
}

// Вычитание чисел
Hex Hex::subtract(const Hex& other) {
    if (other.numSize > this->numSize) {
        throw std::logic_error("Результат вычислений не может быть отрицательным");
    }

    std::vector<unsigned char> result;
    size_t sz = this->numSize;
    size_t i = 0;
    int k = 0;
    unsigned char ch;

    for (; i < sz; ++i) {
        int num = 0;
        int cur1 = 0;
        int cur2 = 0;
        int sub = 0;
        if (!isdigit(this->dataHex[i])) {
            cur1 = static_cast<int> (this->dataHex[i] - 'A' + 10);
        } else {
            cur1 = static_cast<int> (this->dataHex[i] - '0');
        }
        sub = cur1;

        if (i < other.numSize) {
            if (!isdigit(other.dataHex[i])) {
                cur2 = static_cast<int> (other.dataHex[i] - 'A' + 10);
            } else {
                cur2 = static_cast<int> (other.dataHex[i] - '0');
            }
        } else {
            cur2 = 0;
        }

        if (cur1 - k < cur2) {
            sub += 16;
            sub = sub - k - cur2;
            k = 1;
        } else {
            sub = sub - k - cur2;
            k = 0;
        }

        num = sub % 16;

        if (num > 9) {
            ch = static_cast<unsigned char> (num + 'A' - 10);
        } else {
            ch = static_cast<unsigned char> (num + '0');
        }

        result.push_back(ch);
    }

    if (k > 0) {
        throw std::logic_error("Результат вычислений не может быть отрицательным");
    }

    for (int i = 0; i < result.size(); ++i) std::cout << result[i] << std::endl;

    Hex a(result);
    a.print(std::cout);

    std::cout << "asdfvb " << std::endl;

    std::reverse(result.begin(), result.end());
    return Hex(result);
}

// Сравнение чисел на равенство
bool Hex::equals(const Hex& other) const {
    if (this->numSize != other.numSize) return false;

    for (size_t i = 0; i < this->numSize; ++i) {
        if (this->dataHex[i] != other.dataHex[i]) return false;
    }
    return true;
}

// Сравнение чисел (знак больше)
bool Hex::greater(const Hex& other) const {
    if (this->numSize > other.numSize) return true;
    if (this->numSize < other.numSize) return false;

    size_t sz = this->numSize;
    for (size_t i = 0; i < sz; ++i) {
        int this_val = isdigit(this->dataHex[sz - i - 1]) ? this->dataHex[sz - i - 1] - '0' : this->dataHex[sz - i - 1] - 'A' + 10;
        int other_val = isdigit(other.dataHex[sz - i - 1]) ? other.dataHex[sz - i - 1] - '0' : other.dataHex[sz - i - 1] - 'A' + 10;
        if (this_val > other_val) return true;
        if (this_val < other_val) return false;
    }
    return false; // равны
}

// Сравнение чисел (знак меньше)
bool Hex::less(const Hex& other) const {
    return other.greater(*this);
}

// Вывод массива в поток
std::ostream& Hex::print(std::ostream& outputStream) {
    for (size_t i = 0; i < numSize; ++i) {
        outputStream << dataHex[numSize - 1 - i];
    }
    return outputStream;
}

// === РЕАЛИЗАЦИЯ ДЕСТРУКТОРА ===

// Деструктор - освобождает динамическую память
Hex::~Hex() noexcept {    
    if (dataHex != nullptr) {
        delete[] dataHex;
        dataHex = nullptr;
    }

    numSize = 0;
}
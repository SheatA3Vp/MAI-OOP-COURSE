#include "./include/figure_array.hpp"
#include "./include/triangle.hpp"
#include "./include/square.hpp"
#include "./include/octagon.hpp"

int main() {
    std::cout << "Введите одну из команд\n";
    std::cout << "Команды:\n";
    std::cout << "1. Добавить треугольник (3 вершины)\n";
    std::cout << "triangle\n";
    std::cout << "x1 y1 x2 y2 x3 y3\n";
    std::cout << std::endl;
    std::cout << "2. Добавить квадрат (4 вершины)\n";
    std::cout << "square\n";
    std::cout << "x1 y1 x2 y2 x3 y3 x4 y4\n";
    std::cout << std::endl;
    std::cout << "3. Добавить 8-угольник (8 вершин)\n";
    std::cout << "octagon\n";
    std::cout << "x1 y1 ... x8 y8\n";
    std::cout << std::endl;
    std::cout << "4. Вывести центры, площади и общую площадь всех фигур\n";
    std::cout << "print\n";
    std::cout << std::endl;
    std::cout << "5. Удалить фигуру по индексу (начиная с 0)\n";
    std::cout << "remove index\n";
    std::cout << std::endl;
    std::cout << "6. Выйти из программы\n";
    std::cout << "exit\n";
    std::cout << std::endl;
    std::cout << "Введите команды:\n";

    FigureArray arr;
    std::string command;
    while (std::cin >> command) {
        if (command == "triangle") {
            Triangle* t = new Triangle();
            std::cin >> *t;
            arr.add(*t);
        } else if (command == "square") {
            Square* s = new Square();
            std::cin >> *s;
            arr.add(*s);
        } else if (command == "octagon") {
            Octagon* o = new Octagon();
            std::cin >> *o;
            arr.add(*o);
        } else if (command == "print") {
            std::cout << "Centers:" << std::endl;
            arr.array_center();
            std::cout << "Areas:" << std::endl;
            arr.array_square();
            std::cout << "Total area: " << arr.total_area() << std::endl;
        } else if (command == "remove") {
            size_t index;
            std::cin >> index;
            if (index < arr.get_size()) {
                arr.pop(index);
            } else {
                std::cout << "Неверный индекс\n";
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Неизвестная команда. Введите 'exit' для выхода.\n";
        }
    }
    return 0;
}
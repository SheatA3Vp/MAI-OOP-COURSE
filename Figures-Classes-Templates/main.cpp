#include "./include/figure_array.hpp"
#include "./include/trapezoid.hpp"
#include "./include/rhombus.hpp"
#include "./include/pentagon.hpp"

int main() {
    std::cout << "Введите одну из команд\n";
    std::cout << "Команды:\n";
    std::cout << "1. Добавить трапецию (4 вершины)\n";
    std::cout << "trapezoid\n";
    std::cout << "x1 y1 x2 y2 x3 y3 x4 y4\n";
    std::cout << std::endl;
    std::cout << "2. Добавить ромб (4 вершины)\n";
    std::cout << "rhombus\n";
    std::cout << "x1 y1 x2 y2 x3 y3 x4 y4\n";
    std::cout << std::endl;
    std::cout << "3. Добавить пятиугольник (5 вершин)\n";
    std::cout << "pentagon\n";
    std::cout << "x1 y1 x2 y2 x3 y3 x4 y4 x5 y5\n";
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

    Array<Figure<double>*> arr;
    std::string command;
    while (std::cin >> command) {
        try {
            if (command == "trapezoid") {
                Trapezoid<double>* t = new Trapezoid<double>();
                std::cin >> *t;
                arr.add(t);
            } else if (command == "rhombus") {
                Rhombus<double>* r = new Rhombus<double>();
                std::cin >> *r;
                arr.add(r);
            } else if (command == "pentagon") {
                Pentagon<double>* p = new Pentagon<double>();
                std::cin >> *p;
                arr.add(p);
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
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}

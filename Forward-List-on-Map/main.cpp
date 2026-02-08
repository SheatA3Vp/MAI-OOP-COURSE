#include <iostream>
#include <iomanip>
#include "include/memory_resource.hpp"
#include "include/forward_list.hpp"

// Структура для проверки работы со сложными типами
struct Point {
    double x;
    double y;

    Point() : x(0.0), y(0.0) {}
    Point(double x, double y) : x(x), y(y) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << std::fixed << std::setprecision(2) << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {

    std::cout << "ForwardList с пользовательским аллокатором\n";
    MapMemoryResource resource;

    // Пример с int
    {
        ForwardList<int> list(&resource);
        list.push_front(50);
        list.push_front(40);
        list.push_front(30);
        list.push_front(20);
        list.push_front(10);
        std::cout << "int: ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\nsize: " << list.size() << std::endl;
        std::cout << "front: " << list.front() << std::endl;
        list.pop_front();
        std::cout << "после pop_front: size = " << list.size() << std::endl;
        std::cout << "alloc blocks: " << resource.get_allocated_count() << std::endl;
    }
    std::cout << std::endl;

    // Пример со структурой
    {
        ForwardList<Point> list(&resource);
        list.push_front(Point(5.5, 6.5));
        list.push_front(Point(3.0, 4.0));
        list.push_front(Point(1.5, 2.5));
        std::cout << "Point: ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\nsize: " << list.size() << std::endl;
        std::cout << "front: " << list.front() << std::endl;
    }
    std::cout << std::endl;

    // Проверка итератора
    {
        ForwardList<int> list(&resource);

        list.push_front(100);
        list.push_front(200);
        list.push_front(300);
        
        auto it = list.begin();
        std::cout << "iterator: ";
        std::cout << *it << " ";
        ++it;
        std::cout << *it << " ";
        ++it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // Демонстрация переиспользования памяти
    {
        ForwardList<int> list(&resource);
        for (int i = 1; i <= 5; ++i) list.push_front(i);
        std::cout << "alloc blocks: " << resource.get_allocated_count() << std::endl;
        std::cout << "free blocks: " << resource.get_free_blocks_count() << std::endl;
        for (int i = 0; i < 3; ++i) list.pop_front();
        std::cout << "после pop_front: alloc blocks: " << resource.get_allocated_count() << std::endl;
        std::cout << "free blocks: " << resource.get_free_blocks_count() << std::endl;
        list.push_front(10);
        list.push_front(20);
        std::cout << "alloc blocks: " << resource.get_allocated_count() << std::endl;
        std::cout << "free blocks: " << resource.get_free_blocks_count() << std::endl;
        std::cout << "list: ";
        for (auto val : list) std::cout << val << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Итоговое состояние памяти
    std::cout << "alloc blocks: " << resource.get_allocated_count() << std::endl;
    std::cout << "total allocated: " << resource.get_total_allocated() << " bytes" << std::endl;
    return 0;
}


# ForwardList с пользовательским аллокатором

Однонаправленный список с аллокатором на базе std::pmr::memory_resource. Память отслеживается через std::map, поддерживается переиспользование блоков.

## Основные файлы

Главные файлы:
- main.cpp — пример работы
- include/memory_resource.hpp — аллокатор
- include/forward_list.hpp — сам список
- tests/tests.cpp — тесты

## Сборка и запуск

```sh
cd Forward-List-on-Map
mkdir -p build
cd build
cmake ..
make
```

### Запуск

```sh
./Lab05_exe    # демонстрация
./tests        # тесты
```

## Методы

- push_front(value) — добавить в начало
- pop_front() — удалить первый элемент
- front() — получить первый элемент
- clear() — очистить список
- size(), empty(), begin(), end()

## Итератор

- ++, *, ->, ==, !=
- Проверка на null-итератор (выброс исключения)

## Кратко о реализации

- MapMemoryResource наследует std::pmr::memory_resource
- Для отслеживания памяти используются два std::map: allocated_blocks и free_blocks
- При освобождении блоки попадают в free_blocks и могут быть переиспользованы
- В деструкторе вся память очищается
- ForwardList<T> использует std::pmr::polymorphic_allocator
- Итератор реализует forward_iterator_tag

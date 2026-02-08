#pragma once

#include <memory>
#include <memory_resource>
#include <iterator>
#include <stdexcept>

template <typename T>
class ForwardList {
private:
    struct Node {
        T data;
        Node* next;
        
        template <typename U>
        Node(U&& value)
            : data(std::forward<U>(value)), next(nullptr) {}
    };

    std::pmr::polymorphic_allocator<Node> node_allocator;
    Node* head;
    std::size_t size_;

public:
    // Forward iterator
    class ForwardIterator {
    private:
        Node* current;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        explicit ForwardIterator(Node* node = nullptr) : current(node) {}

        reference operator*() const {
            if (current == nullptr) {
                throw std::out_of_range("Dereferencing null iterator");
            }
            return current->data;
        }

        pointer operator->() const {
            if (current == nullptr) {
                throw std::out_of_range("Dereferencing null iterator");
            }
            return &current->data;
        }

        ForwardIterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        ForwardIterator operator++(int) {
            ForwardIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const ForwardIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const ForwardIterator& other) const {
            return current != other.current;
        }

        friend class ForwardList;
    };

    using iterator = ForwardIterator;
    using const_iterator = ForwardIterator;

    // Конструктор
    explicit ForwardList(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : node_allocator(resource), head(nullptr), size_(0) {}

    // Деструктор
    ~ForwardList() {
        clear();
    }

    // Конструктор перемещением
    ForwardList(ForwardList&& other) noexcept
        : node_allocator(other.node_allocator.resource()), head(other.head), size_(other.size_) {
        other.head = nullptr;
        other.size_ = 0;
    }

    // Оператор перемещения
    ForwardList& operator=(ForwardList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            size_ = other.size_;
            node_allocator = other.node_allocator;
            other.head = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Конструктор копирования
    ForwardList(const ForwardList& other)
        : node_allocator(other.node_allocator.resource()), head(nullptr), size_(0) {
        Node* current = other.head;
        Node* prev = nullptr;
        
        while (current != nullptr) {
            Node* new_node = node_allocator.allocate(1);
            new (new_node) Node(current->data);
            
            if (prev == nullptr) {
                head = new_node;
            } else {
                prev->next = new_node;
            }
            prev = new_node;
            current = current->next;
            ++size_;
        }
    }

    // Оператор присваивания копированием
    ForwardList& operator=(const ForwardList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            Node* prev = nullptr;
            
            while (current != nullptr) {
                Node* new_node = node_allocator.allocate(1);
                new (new_node) Node(current->data);
                
                if (prev == nullptr) {
                    head = new_node;
                } else {
                    prev->next = new_node;
                }
                prev = new_node;
                current = current->next;
                ++size_;
            }
        }
        return *this;
    }

    // Push front
    template <typename U>
    void push_front(U&& value) {
        Node* new_node = node_allocator.allocate(1);
        new (new_node) Node(std::forward<U>(value));
        new_node->next = head;
        head = new_node;
        ++size_;
    }

    // Pop front
    void pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("pop_front on empty list");
        }
        Node* temp = head;
        head = head->next;
        temp->~Node();
        node_allocator.deallocate(temp, 1);
        --size_;
    }

    // Front access
    T& front() {
        if (head == nullptr) {
            throw std::out_of_range("front on empty list");
        }
        return head->data;
    }

    const T& front() const {
        if (head == nullptr) {
            throw std::out_of_range("front on empty list");
        }
        return head->data;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            temp->~Node();
            node_allocator.deallocate(temp, 1);
        }
        size_ = 0;
    }

    std::size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    // Iterator
    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const {
        return const_iterator(head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    const_iterator cbegin() const {
        return const_iterator(head);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }
};
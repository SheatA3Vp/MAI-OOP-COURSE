#pragma once

#include <memory>
#include <memory_resource>
#include <map>
#include <vector>
#include <stdexcept>

class MapMemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, std::size_t> allocated_blocks;
    std::map<std::size_t, std::vector<void*>> free_blocks;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        // Пробуем переиспользовать память того же размера
        auto it = free_blocks.find(bytes);
        if (it != free_blocks.end() && !it->second.empty()) {
            void* ptr = it->second.back();
            it->second.pop_back();
            allocated_blocks[ptr] = bytes;
            return ptr;
        }

        // Если не вышло переиспользовать
        void* ptr = operator new(bytes);
        allocated_blocks[ptr] = bytes;
        return ptr;
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) noexcept override {
        if (p == nullptr) return;
        
        auto it = allocated_blocks.find(p);
        if (it != allocated_blocks.end()) {
            std::size_t size = it->second;
            allocated_blocks.erase(it);
            // Добавляем в пул как блок который можно переиспользовать 
            free_blocks[size].push_back(p);
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

public:
    ~MapMemoryResource() override {
        for (auto& [ptr, size] : allocated_blocks) {
            operator delete(ptr);
        }
        allocated_blocks.clear();

        for (auto& [size, blocks] : free_blocks) {
            for (void* ptr : blocks) {
                operator delete(ptr);
            }
        }
        free_blocks.clear();
    }

    // Методы для получения информации для тестов
    std::size_t get_allocated_count() const {
        return allocated_blocks.size();
    }

    std::size_t get_total_allocated() const {
        std::size_t total = 0;
        for (const auto& [ptr, size] : allocated_blocks) {
            total += size;
        }
        return total;
    }
    
    std::size_t get_free_blocks_count() const {
        std::size_t total = 0;
        for (const auto& [size, blocks] : free_blocks) {
            total += blocks.size();
        }
        return total;
    }
};

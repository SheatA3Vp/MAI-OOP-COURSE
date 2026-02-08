#include <gtest/gtest.h>
#include "../include/memory_resource.hpp"
#include "../include/forward_list.hpp"
#include <memory_resource>

// Структура для тестирования со несколькими полями
struct TestData {
    int id;
    double value;
    std::string name;
    
    TestData() : id(0), value(0.0), name("") {}
    TestData(int id, double value, const std::string& name) 
        : id(id), value(value), name(name) {}
    
    bool operator==(const TestData& other) const {
        return id == other.id && value == other.value && name == other.name;
    }
};

// ============== ТЕСТЫ MEMORY RESOURCE ==============

TEST(MemoryResourceTest, AllocateDeallocate) {
    MapMemoryResource resource;
    
    void* ptr1 = resource.allocate(100, 8);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_EQ(resource.get_allocated_count(), 1);
    
    void* ptr2 = resource.allocate(200, 8);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(resource.get_allocated_count(), 2);
    
    resource.deallocate(ptr1, 100, 8);
    EXPECT_EQ(resource.get_allocated_count(), 1);
    
    resource.deallocate(ptr2, 200, 8);
    EXPECT_EQ(resource.get_allocated_count(), 0);
}

TEST(MemoryResourceTest, TotalAllocatedMemory) {
    MapMemoryResource resource;
    
    void* ptr1 = resource.allocate(100, 8);
    void* ptr2 = resource.allocate(200, 8);
    
    EXPECT_EQ(resource.get_total_allocated(), 300);
    
    resource.deallocate(ptr1, 100, 8);
    EXPECT_EQ(resource.get_total_allocated(), 200);
}

TEST(MemoryResourceTest, DestructorCleansup) {
    {
        MapMemoryResource resource;
        void* ptr1 = resource.allocate(100, 8);
        void* ptr2 = resource.allocate(200, 8);
        EXPECT_EQ(resource.get_allocated_count(), 2);
    }
}

TEST(MemoryResourceTest, DeallocateNull) {
    MapMemoryResource resource;
    // Должна корректно обработать null-указатель без ошибок
    resource.deallocate(nullptr, 0, 8);  // NOLINT
    EXPECT_EQ(resource.get_allocated_count(), 0);
}

// ============== ТЕСТЫ FORWARD-ЛИСТА С INT ==============

TEST(ForwardListIntTest, PushFrontSingleElement) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(42);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
}

TEST(ForwardListIntTest, PushFrontMultipleElements) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 3);
}

TEST(ForwardListIntTest, PopFront) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    
    EXPECT_EQ(list.size(), 3);
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 20);
    
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
}

TEST(ForwardListIntTest, PopFrontEmpty) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(ForwardListIntTest, FrontEmpty) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    EXPECT_THROW(list.front(), std::out_of_range);
}

TEST(ForwardListIntTest, Clear) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ForwardListIntTest, Empty) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    EXPECT_TRUE(list.empty());
    list.push_front(42);
    EXPECT_FALSE(list.empty());
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

// ============== ТЕСТЫ ИТЕРАТОРОВ ==============

TEST(IteratorTest, BeginEnd) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    
    auto it = list.begin();
    EXPECT_NE(it, list.end());
    EXPECT_EQ(*it, 10);
}

TEST(IteratorTest, Increment) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    
    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    
    ++it;
    EXPECT_EQ(*it, 20);
    
    ++it;
    EXPECT_EQ(*it, 30);
    
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(IteratorTest, PostIncrement) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(2);
    list.push_front(1);
    
    auto it = list.begin();
    auto old_it = it++;
    
    EXPECT_EQ(*old_it, 1);
    EXPECT_EQ(*it, 2);
}

TEST(IteratorTest, IterateAllElements) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(5);
    list.push_front(4);
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    int expected[] = {1, 2, 3, 4, 5};
    int index = 0;
    
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[index]);
        index++;
    }
    EXPECT_EQ(index, 5);
}

TEST(IteratorTest, ArrowOperator) {
    MapMemoryResource resource;
    ForwardList<TestData> list(&resource);
    
    list.push_front(TestData(1, 3.14, "pi"));
    
    auto it = list.begin();
    EXPECT_EQ(it->id, 1);
    EXPECT_DOUBLE_EQ(it->value, 3.14);
    EXPECT_EQ(it->name, "pi");
}

// ============== ТЕСТЫ FORWARD-ЛИСТА СО СЛОЖНЫМИ ТИПАМИ ==============

TEST(ForwardListComplexTest, PushComplexType) {
    MapMemoryResource resource;
    ForwardList<TestData> list(&resource);
    
    list.push_front(TestData(1, 1.5, "one"));
    list.push_front(TestData(2, 2.5, "two"));
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front().id, 2);
}

TEST(ForwardListComplexTest, IterateComplexType) {
    MapMemoryResource resource;
    ForwardList<TestData> list(&resource);
    
    list.push_front(TestData(3, 3.0, "three"));
    list.push_front(TestData(2, 2.0, "two"));
    list.push_front(TestData(1, 1.0, "one"));
    
    TestData expected[] = {
        TestData(1, 1.0, "one"),
        TestData(2, 2.0, "two"),
        TestData(3, 3.0, "three")
    };
    
    int index = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[index]);
        index++;
    }
}

TEST(ForwardListComplexTest, ClearComplexType) {
    MapMemoryResource resource;
    ForwardList<TestData> list(&resource);
    
    list.push_front(TestData(1, 1.5, "one"));
    list.push_front(TestData(2, 2.5, "two"));
    
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

// ============== ТЕСТЫ КОМБИНИРОВАННЫХ ОПЕРАЦИЙ ==============

TEST(MixedOperationsTest, PushPopSequence) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(10);
    list.push_front(20);
    list.pop_front();
    list.push_front(30);
    list.push_front(40);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 40);
    
    list.pop_front();
    EXPECT_EQ(list.front(), 30);
    list.pop_front();
    EXPECT_EQ(list.front(), 10);
}

TEST(MixedOperationsTest, LargeNumberOfElements) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    const int N = 1000;
    for (int i = 0; i < N; ++i) {
        list.push_front(i);
    }
    
    EXPECT_EQ(list.size(), N);
    
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, N);
}

TEST(MixedOperationsTest, MemoryResourceTracking) {
    MapMemoryResource resource;
    
    {
        ForwardList<int> list(&resource);
        list.push_front(1);
        list.push_front(2);
        list.push_front(3);
        
        EXPECT_EQ(resource.get_allocated_count(), 3);
        
        list.pop_front();
        EXPECT_EQ(resource.get_allocated_count(), 2);
        
        list.clear();
        // После очистки счётчик должен обнулиться
        EXPECT_EQ(resource.get_allocated_count(), 0);
    }
    
    // После уничтожения списка ничего не должно остаться
    EXPECT_EQ(resource.get_allocated_count(), 0);
}

// ============== ТЕСТЫ КОРРЕКТНОСТИ ИТЕРАТОРОВ ==============

TEST(IteratorValidityTest, DereferenceNullIterator) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    auto it = list.end();
    EXPECT_THROW(*it, std::out_of_range);
}

TEST(IteratorValidityTest, ArrowOperatorNullIterator) {
    MapMemoryResource resource;
    ForwardList<TestData> list(&resource);
    
    auto it = list.end();
    EXPECT_THROW(it->id, std::out_of_range);  // NOLINT
}

// ============== ТЕСТЫ ОПЕРАЦИЙ КОПИРОВАНИЯ ==============

TEST(CopyConstructorTest, CopyEmptyList) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    
    ForwardList<int> list2 = list1;
    
    EXPECT_TRUE(list2.empty());
    EXPECT_EQ(list2.size(), 0);
}

TEST(CopyConstructorTest, CopyNonEmptyList) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    
    list1.push_front(3);
    list1.push_front(2);
    list1.push_front(1);
    
    ForwardList<int> list2 = list1;
    
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    
    auto it = list2.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(CopyConstructorTest, CopyIsIndependent) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    
    list1.push_front(10);
    list1.push_front(20);
    
    ForwardList<int> list2 = list1;

    list1.pop_front();

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 20);

    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list1.front(), 10);
}

TEST(CopyConstructorTest, CopyWithComplexTypes) {
    MapMemoryResource resource;
    ForwardList<TestData> list1(&resource);
    
    list1.push_front(TestData(1, 1.5, "one"));
    list1.push_front(TestData(2, 2.5, "two"));
    
    ForwardList<TestData> list2 = list1;
    
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front().id, 2);
    EXPECT_EQ(list2.front().name, "two");
}

TEST(CopyAssignmentTest, AssignToEmptyList) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    list1.push_front(1);
    list1.push_front(2);
    
    ForwardList<int> list2(&resource);
    list2 = list1;
    
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 2);
}

TEST(CopyAssignmentTest, AssignToNonEmptyList) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    list1.push_front(100);
    list1.push_front(200);
    
    ForwardList<int> list2(&resource);
    list2.push_front(10);
    list2.push_front(20);
    list2.push_front(30);
    
    EXPECT_EQ(list2.size(), 3);
    
    list2 = list1;
    
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 200);
}

TEST(CopyAssignmentTest, SelfAssignment) {
    MapMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    
    list = list;

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 3);
}

TEST(CopyAssignmentTest, CopyAssignmentIndependent) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    list1.push_front(10);
    list1.push_front(20);
    
    ForwardList<int> list2(&resource);
    list2 = list1;
    list2.pop_front();
    list2.push_front(99);

    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list1.front(), 20);

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 99);
}

TEST(CopyOperationsTest, ChainedCopy) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    
    ForwardList<int> list2(&resource);
    ForwardList<int> list3(&resource);
    
    list2 = list1;
    list3 = list2;
    
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list3.size(), 3);

    list1.pop_front();
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list3.size(), 3);
}

TEST(CopyOperationsTest, LargeListCopy) {
    MapMemoryResource resource;
    ForwardList<int> list1(&resource);
    
    const int N = 100;
    for (int i = 0; i < N; ++i) {
        list1.push_front(i);
    }
    
    ForwardList<int> list2 = list1;
    
    EXPECT_EQ(list2.size(), N);

    int count = 0;
    for (auto it = list2.begin(); it != list2.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, N);
}

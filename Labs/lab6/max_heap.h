#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>

template <typename T>
class MaxHeap {
private:
    std::vector<T> data;
public:
    void push(const T& item);
    // Removes the largest element in the heap
    void pop();
    // Returns the largest element in the heap (but does not remove it)
    T const& top() const;
    std::size_t size() const;
};

template <typename T>
void MaxHeap<T>::push(const T& item) {
    data.push_back(item);
    std::size_t index = data.size() - 1;
    while (index != 0) {
        std::size_t parent_index = (index - 1) / 2;
        T& current = data[index];
        T& parent = data[parent_index];
        if (current <= parent) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

template <typename T>
void MaxHeap<T>::pop() {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    std::swap(data.front(), data.back());
    data.pop_back();
    if (data.empty())
    {
        return;
    }
    std::size_t index = 0;
    while(true)
    {
        T& current = data[index];
        std::size_t child1_index = index*2 +1;
        std::size_t child2_index = child1_index +1;
        std::size_t bigChildIndex = index;
        if (child1_index < data.size())
        {
            bigChildIndex = child1_index;
        }
        if (child2_index < data.size() && data[child1_index] > data[child2_index])
        {
            bigChildIndex = child2_index;
        }
        if (bigChildIndex == index || data[bigChildIndex] <= current)
        {
            break;
        }
        std::swap(current, data[bigChildIndex]);
        index = bigChildIndex;
    }
}

template <typename T>
T const& MaxHeap<T>::top() const {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    return data[0];
}

template <typename T>
std::size_t MaxHeap<T>::size() const {
    return data.size();
}

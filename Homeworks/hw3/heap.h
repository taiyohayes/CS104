#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

private:
  std::vector<T> vec;
  int ary;
  PComparator comp;
  void heapify(int loc);
  void trickleUp(int loc);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
: ary(m), comp(c)
{
  vec.clear();
}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  vec.push_back(item);
  trickleUp(vec.size()-1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty())
  {
    throw std::underflow_error("Heap is empty");
  }
  return vec[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty())
  {
    throw std::underflow_error("Heap is empty");
  }
  vec[0] = vec.back();
  vec.pop_back();
  if(empty())
  {
    return;
  }
  heapify(0);

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return vec.empty();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int loc)
{
  int children[ary+1];
  for (int i = 0; i < ary; i++)
  {
    children[i] = ary*loc + i+1;
  }
  int bestChild = loc;
  for (int i = 0; i < ary; i++)
  {
    if (children[i] < int(vec.size()) && comp(vec[children[i]], vec[bestChild]) == true)
    {
      bestChild = children[i];
    }
  }
  if (bestChild == loc || comp(vec[bestChild], vec[loc]) == false)
  {
    return;
  }
  std::swap(vec[loc], vec[bestChild]);
  heapify(bestChild);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
  int parent = (loc-1) / ary;
  if (parent >= 0 && comp(vec[loc], vec[parent]) == true)
  {
    std::swap(vec[loc], vec[parent]);
    trickleUp(parent);
  }
}
#endif


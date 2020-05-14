#ifndef HEAP_HH_
#define HEAP_HH_

#include <iostream>

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <vector>

template <typename E>
using Cmp = int(const E& e1, const E& e2);

template <typename E>
class MaxHeap {
public:
  MaxHeap(Cmp<E>* cmp, const E array[]=nullptr, int nElements=0)
    : cmp(cmp), nElements(nElements)
  {
    for (auto i = 0; i < nElements; ++i) {
      heap.push_back(array[i]);
    }
  }

  void enqueue(E value) {
    heap.push_back(value); //add value at end
    nElements++;
    assert(nElements == static_cast<int>(heap.size()) && "size mismatch");
    for (int pos = nElements - 1; //pos of added value
	 pos != 0 && cmp(heap[pos], heap[parent(pos)]) > 0;
	 pos = parent(pos)) {
      swap(pos, parent(pos));
    }
  }
  
  E dequeue() {
    assert(nElements > 0 && "heap is empty");
    assert(nElements == static_cast<int>(heap.size()) && "size mismatch");
    E value = heap[0];
    heap[0] = heap[nElements - 1]; //put last element at root
    nElements--; heap.pop_back(); //delete it
    if (nElements > 0) siftDown(0);  //move it to correct position
    assert(nElements == static_cast<int>(heap.size()) && "size mismatch");
    return value;
  }

  int size() { return nElements; }

private:
  Cmp<E> *cmp;
  int nElements;
  std::vector<E> heap;

  /** Heapify heap [0, nElements). */
  void buildHeap() {
    assert(nElements == static_cast<int>(heap.size()) && "size mismatch");
    //move internal nodes down if necessary
    for (int i = nElements/2 - 1; i >= 0; --i) {
      siftDown(i);
    }
  }

  /** Move element at pos down in the tree until it is greater
   *  than either of its two children.
   *  When it is necessary to move down, prefer to move down
   *  into subtree with the greater root. 
   */
  void siftDown(int pos) {
    assert(0 <= pos && pos < nElements);
    assert(nElements == static_cast<int>(heap.size()) && "size mismatch");
    while (!isLeaf(pos)) {
      int leftKidPos = leftChild(pos);
      //there must be a left kid since pos is not a leaf
      assert(0 <= leftKidPos && leftKidPos < nElements);
      int rightKidPos = rightChild(pos);
      int maxKidPos =
	(rightKidPos >= 0 && cmp(heap[rightKidPos], heap[leftKidPos]) > 0)
	? rightKidPos
	: leftKidPos;
      if (cmp(heap[pos], heap[maxKidPos]) >= 0) return;
      swap(pos, maxKidPos);
      pos = maxKidPos;
    }
  }

  void swap(int pos1, int pos2) {
    assert(0 <= pos1 && pos1 < nElements);
    assert(0 <= pos2 && pos2 < nElements);
    E tmp = heap[pos1];
    heap[pos1] = heap[pos2];
    heap[pos2] = tmp;
  }

  //tree accessors
  bool isLeaf(int pos) const {
    return (pos >= nElements/2) && (pos < nElements);
  }

  int leftChild(int pos) {
    return (2*pos + 1 < nElements) ? 2*pos + 1 : -1;
  }

  int rightChild(int pos) {
    return (2*pos + 2 < nElements) ? 2*pos + 2 : -1;
  }

  int parent(int pos) {
    return (pos > 0) ? (pos - 1)/2 : -1;
  }

  template <typename E1>
  friend std::ostream& operator<<(std::ostream& out, const MaxHeap<E1>& heap);
};

template <typename E>
std::ostream&
operator<<(std::ostream& out, const MaxHeap<E>& heap) {
  out << "[ ";
  for (int i = 0; i < heap.nElements; i++) {
    out << heap.heap[i] << " ";
  }
  out << "]";
  return out;
}


#endif //#ifndef HEAP_HH_

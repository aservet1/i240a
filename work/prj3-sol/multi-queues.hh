#ifndef MULTI_QUEUES_HH_
#define MULTI_QUEUES_HH_

#include <iostream>

#include "job.hh"
#include "heap.hh"

class MultiQueue {
public:
  MultiQueue(std::ostream& out);
  void enter(const Job& job);
  void move();
  void leave();
private:
  MaxHeap<Job> q0;
  MaxHeap<Job> q1;
  std::ostream& out;
};

#endif //MULTI_QUEUES_HH_

#include "heap.hh"

static int intCmp(const int& a, const int& b) { return a - b; }


/** prefix of  argv[] elements which are ints used to 
 *  to initialize heap; if remaining arg starts is
 *  +VAL, then VAL enqueued onto heap; if "-", then
 *  a value is dequeued from heap.
 */
int main(int argc, char* argv[]) {
  enum { MAX_INIT_SIZE = 16 };
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " INT... [+INT|-]" << std::endl;
    exit(1);							       
  }
  std::ostream& out = std::cout;
  int argvIndex;
  int nElements = 0;
  int array[MAX_INIT_SIZE];
  for (argvIndex = 1; argvIndex < argc; argvIndex++) {
    const char* arg = argv[argvIndex];
    if (!isdigit(arg[0])) break;
    assert(nElements < MAX_INIT_SIZE && "too many initial elements");
    array[nElements++] = atoi(arg);
  }
  MaxHeap<int> heap(intCmp, array, nElements);
  out << "initial heap: " << heap << std::endl;
  for (; argvIndex < argc; ++argvIndex) {
    const char* arg = argv[argvIndex];
    if (arg[0] == '+') {
      int value = atoi(&arg[1]);
      heap.enqueue(value);
      out << "enqueued " << value << ": " << heap << std::endl;
    }
    else {
      assert(strcmp(arg, "-") == 0 && "invalid argv[] value");
      int value = heap.dequeue();
      out << "dequeued " << value << ": " << heap << std::endl;
    }
  }
}



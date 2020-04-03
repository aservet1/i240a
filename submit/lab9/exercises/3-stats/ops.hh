#ifndef OPS_HH_
#define OPS_HH_

#include<iostream>

/** sorting operations */
class Ops {
public:

  /** return < 0, == 0, > 0 if a < b, a == b, a > b */
  virtual int compare(int a, int b);

  /** swap a[i] and a[j] */
  virtual void swap(int a[], int i, int j);

};

class MyOps : public Ops {
  public:

    int nCompares;
    int nSwaps;

    //* constructor */
    MyOps() : nCompares(0), nSwaps(0) {}

    int compare(int a, int b) {
      nCompares++;
      return this->Ops::compare(a,b);
    }

    void swap(int a[], int i, int j) {
      nSwaps++;
      this->Ops::swap(a,i,j);
    }

};

#endif //ifndef OPS_HH_

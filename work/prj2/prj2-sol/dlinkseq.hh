#ifndef DLINK_SEQ_HH_
#define DLINK_SEQ_HH_

#include "seq.hh"

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

template <typename E> class DLinkSeqConstIter;

/** Doubly-linked list node */
template <typename E>
class DLink {

public:
  E element;   //value for this node
  DLink *next; //pointer to next node in list
  DLink *prev; //pointer to previous node in the list

  //constructors
  DLink(const E& elemval, DLink *prevp, DLink* nextp) :
    element(elemval), next(nextp), prev(prevp)
  { }
  DLink(DLink *prevp = nullptr, DLink* nextp = nullptr) :
    next(nextp), prev(prevp)
  { }

};

/** Linked list implementation */
template <typename E> class DLinkSeq : public Seq<E> {
private:

  DLink<E>* head; //pointer to list header
  DLink<E>* tail; //pointer to last element
  int count;      //size of list

  void init() { // Intialization helper method
    head = new DLink<E>;
    head->next = tail = new DLink<E>(head, nullptr);
    count = 0;
  }
  void removeall() {
    while (head != nullptr) {
      DLink<E>* curr = head;
      head = head->next;
      delete curr;
    }
  }

  friend class DLinkSeqConstIter<E>;

  enum class Private { TAG };
public:

  /** constructor */
  //make_unique requires this constructor to be public
  //by adding first argument, make it impossible to be called directly
  //from outside this class
  DLinkSeq(Private tag) { init(); }

  /** factory function */
  static SeqPtr<E> make() {
    return std::make_unique<DLinkSeq<E>>(Private::TAG);
  }

  //destructor
  ~DLinkSeq() { removeall(); }

  /** empty out the list */
  void clear() { removeall(); init(); }

  /** add item to the start of this seq. */
  void unshift(const E& it)
  {
    DLink<E>* temp = new DLink<E>(it,nullptr,head);
    head->prev = temp;
    temp->next = head;
    head = temp;
    count++;
  }

  /** remove and return first item from this seq.
   *  fails if this seq is empty.
   */
  E shift()
  {
    E it = head->element;
    DLink<E>* temp = head;
    head = head->next;
    delete temp;
    count--;
    return it;
  }

  /** append "it" to this list */
  void push(const E& it) {
    tail->prev = tail->prev->next =
      new DLink<E>(it, tail->prev, tail);
    count++;
  }

  /** remove and return last item from this seq.
   *  fails if this seq is empty.
   */
  E pop()
  {
    assert(count > 0 && "pop on empty dlink seq");
    E val = tail->element;
    DLink<E>* temp = tail;
    tail = tail->prev;
    delete temp;
    count--;
    return val;
  }

  /** return number of elements currently in this */
  int size() const { return count; }

  /** Return an iterator initialized to start of this seq */
  ConstIterPtr<E> cbegin() const {
    const DLinkSeq* constThis = static_cast<const DLinkSeq*>(this);
    return std::make_unique<DLinkSeqConstIter<E>>(constThis);
  }

  /** Return an iterator initialized to end of this seq */
  virtual ConstIterPtr<E> cend() const {
    const DLinkSeq* constThis = static_cast<const DLinkSeq*>(this);
    return std::make_unique<DLinkSeqConstIter<E>>(constThis, false);
  }

};

template <typename E>
class DLinkSeqConstIter : public ConstIter<E> {
public:

  DLinkSeqConstIter(const DLinkSeq<E>* const seq, bool isHead=true)
    : seq(seq), link(isHead ? seq->head->next : seq->tail->prev)
  { }

  /** pre-increment */
  DLinkSeqConstIter& operator++() {
    link = link->next;
    return *this;
  }

  /** pre-decrement */
  DLinkSeqConstIter& operator--() {
    link = link->prev;
    return *this;
  }

  /** return true iff this pointer is not "NULL" */
  virtual operator bool() {
    return link == seq->head || link == seq->tail;
  }

  /** Return element this is pointing to */
  const E& operator*() {
    return link->element;
  }

  /** Return pointer to element this is pointing to */
  const E* operator->() {
    return &(link->element);
  }

private:
  const DLinkSeq<E>* const seq;
  DLink<E>* link;
};


#endif //ifndef ARRAY_SEQ_HH_

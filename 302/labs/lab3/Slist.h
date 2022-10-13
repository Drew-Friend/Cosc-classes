#ifndef SLIST_H
#define SLIST_H
// include header file(s) needed

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
// qsort_r3: randomly chosen pivot, 3-way partition {<},{=},{>}

// template <typename T>
template <class T> class slist {
private:
  struct node {
    node() {
      data = T();
      next = NULL;
    }
    node(const T &key) {
      data = key;
      next = NULL;
    }
    bool operator<(node &other) { return data < other.data; }

    T data;
    node *next;
  };

  node *head;
  node *tail;
  // add class sptr { write this for node data }
  class sptr {
  public:
    sptr(node *_ptr = NULL) { ptr = _ptr; }
    bool operator<(const sptr &rhs) const { return *ptr < *rhs.ptr; }
    operator node *() const { return ptr; }

  private:
    node *ptr;
  };

public:
  class iterator {
  public:
    iterator() { p = NULL; }
    T &operator*() { return p->data; }
    iterator &operator++() {
      p = p->next;
      return *this;
    }
    bool operator!=(const iterator &rhs) const { return p != rhs.p; }

  private:
    iterator(node *n_p) { p = n_p; }
    node *p;

    friend class slist<T>;
  };

  slist();
  ~slist();

  void push_back(const T &);
  void sort(const std::string &);

  iterator begin() { return iterator(head->next); }
  iterator end() { return iterator(NULL); }
};

template <typename T> slist<T>::slist() {
  head = new node();
  tail = head;
}

template <typename T> slist<T>::~slist() {
  while (head->next != NULL) {
    node *p = head->next;
    head->next = p->next;
    delete p;
  }
  delete head;

  head = NULL;
  tail = NULL;
}

template <typename T> void slist<T>::push_back(const T &din) {
  tail->next = new node(din);
  tail = tail->next;
}

template <typename T> void slist<T>::sort(const std::string &algname) {
  // determine number of list elements
  // set up smart pointer array called Ap
  // if quicksort, apply std::sort(...)
  // if mergesort, apply std::stable_sort(...)
  // if qsort_r3, apply qsort_r3(...)
  // use sorted Ap array to relink list
  std::vector<sptr> Ap;
  for (node *i = head->next; i->next; i = i->next)
    Ap.push_back(sptr(i));
  
  if (algname == "-quicksort")
    std::sort(Ap.begin(), Ap.end());
  else if (algname == "-mergesort")
    std::stable_sort(Ap.begin(), Ap.end());
  head->next = Ap[0];
  node *curr = head->next;
  for (int i = 1; i < Ap.size(); ++i) {
    curr->next = Ap[i];
    curr = curr->next;
  }
  curr->next = NULL;
}

#endif // SLIST_H

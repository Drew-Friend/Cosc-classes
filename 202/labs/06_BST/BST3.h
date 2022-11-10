#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey> class bst {
  struct node {
    node(int = 0);

    void print();

    TKey key;
    int ID;

    // parent info
    node *pLink;
    node *link[2];
  };

public:
  class iterator {
  public:
    // default constructor (no argument)
    iterator() { p = NULL; }
    iterator *operator++();
    bool operator==(const iterator &other) const { return (other.p == p); }
    TKey operator*() { return p->key; }

  private:
    friend class bst<TKey>;
    iterator(node *start) { p = start; }

    node *p;
  };

  iterator begin() {
    iterator T;
    T.p = Troot;
    while (T.p->link[0])
      T.p = T.p->link[0];
    return T;
  }
  iterator end() { return iterator(); }

  iterator lower_bound(const TKey &);
  iterator upper_bound(const TKey &);

  bst() {
    Troot = NULL;
    nodeID = 1;
  }
  ~bst() { clear(Troot); }

  bool empty() { return Troot == NULL; }

  void insert(TKey &);

  void print_bylevel();

private:
  void clear(node *);
  node *insert(node *, TKey &);

  // ID parameter
  int nodeID;
  node *Troot;
};

// bst<TKey>::node constructor goes here
template <class TKey> bst<TKey>::node::node(int id) {
  ID = id;
  pLink = nullptr;
  link[0] = nullptr;
  link[1] = nullptr;
}

template <class TKey> void bst<TKey>::node::print() {
  cout << ID;
  cout << setw(3) << key << " :";
  if (pLink)
    cout << "P=" << setw(3) << pLink->ID;
  else
    cout << "ROOT ";

  // output node and parent ID information
  // change below to output subtree ID information

  if (link[0])
    cout << " L=" << setw(3) << link[0]->ID;
  else
    cout << "      ";
  if (link[1])
    cout << " R=" << setw(3) << link[1]->ID;
  else
    cout << "      ";

  cout << "\n";
}

// specialized string version of the above goes here
template <> void bst<string>::node::print() {
  cout << ID;
  cout << setw(20) << key << " :";
  if (pLink)
    cout << "P=" << setw(3) << pLink->ID;
  else
    cout << "ROOT ";

  // output node and parent ID information
  // change below to output subtree ID information

  if (link[0])
    cout << " L=" << setw(3) << link[0]->ID;
  else
    cout << "      ";
  if (link[1])
    cout << " R=" << setw(3) << link[1]->ID;
  else
    cout << "      ";

  cout << "\n";
}

// bst<TKey>::iterator functions not defined above go here

template <class TKey> void bst<TKey>::clear(node *T) {
  if (T) {
    clear(T->link[0]);
    clear(T->link[1]);
    delete T;
    T = NULL;
  }
}

template <class TKey> void bst<TKey>::insert(TKey &key) {
  Troot = insert(Troot, key);
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key) {
  // set parent link below
  if (T == NULL) {
    // update and set node ID
    T = new node(nodeID++);
    T->key = key;
  } else if (T->key == key) {
    ;
  } else if (key < T->key) {
    T->link[0] = insert(T->link[0], key);
    T->link[0]->pLink = T;
  } else {
    T->link[1] = insert(T->link[1], key);
    T->link[1]->pLink = T;
  }
  return T;
}

template <class TKey>
class bst<TKey>::iterator *bst<TKey>::iterator::operator++() {
  // If no right branch, go up and return that parent.
  // If there's a right branch, take it, then go to the leftmost point from
  // there
  if (!(p->link[1])) {
    if (!p->pLink) {
      p = NULL;
      return this;
    }
    while (p == p->pLink->link[1]) {
      p = p->pLink;
      if (!p->pLink)
        break;
      if (p == p->pLink->link[1] && p->pLink->pLink == NULL) {
        p = NULL;
        return this;
      }
    }
    p = p->pLink;
  }
  // if(!(p->link[1]))
  else {
    p = p->link[1];
    while (p->link[0])
      p = p->link[0];
  }
  return this;
}

template <class TKey>
class bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &val) {
  iterator view(Troot);
  node *standard = view.p;
  bool done = false;
  // Each cycle, plinko down a level
  // Left if greater, then right if less
  // Update the baseline with the new position if it's a better, valid, option
  // At the end, if the baseline isn't valid, that means no valid node exists
  // Logic is the same in lower_bound
  while (!done) {
    done = true;
    if (*view > val) {
      if (view.p->link[0]) {
        view.p = view.p->link[0];
        done = false;
      }
    }
    if (*view <= val) {
      if (view.p->link[1]) {
        view.p = view.p->link[1];
        done = false;
      }
    }
    if (view.p->key > val &&
        (view.p->key < standard->key) == (standard->key > val))
      standard = view.p;
  }
  view.p = (standard->key > val) ? standard : NULL;
  return view;
}

template <class TKey>
class bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &val) {
  iterator view(Troot);
  node *standard = view.p;
  int prev;
  bool done = false;
  while (!done) {
    done = true;
    if (*view > val) {
      if (view.p->link[0]) {
        view.p = view.p->link[0];
        done = false;
      }
    }
    if (*view < val) {
      if (view.p->link[1]) {
        view.p = view.p->link[1];
        done = false;
      }
    }
    if (view.p->key >= val &&
        (view.p->key < standard->key) == (standard->key > val))
      standard = view.p;
  }
  view.p = (standard->key >= val) ? standard : NULL;
  return view;
}

template <class TKey>
void bst<TKey>::print_bylevel() {
  if (Troot == NULL)
    return;

  queue<node *> Q;
  node *T;

  Q.push(Troot);
  while (!Q.empty()) {
    T = Q.front();
    Q.pop();

    T->print();
    if (T->link[0])
      Q.push(T->link[0]);
    if (T->link[1])
      Q.push(T->link[1]);
  }
}
#endif

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

// bst<TKey>::lower_bound function goes here

// bst<TKey>::upper_bound function goes here

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

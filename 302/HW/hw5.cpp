// Extra credit for hw5, implimentation of merge sort
template <typename node>

node *merge(node *L, node *M, node *R) {
  node *p = L;
  node *q = M;
  node *pH;
  while (*q != *R) {
    if (p->data < q->data)
      p = p->next;
    else {
      q->prev->next = q->next;
      q->next->prev = q->prev;
      pH = q->next;
      q->next = p;
      q->prev = p->prev;
      p->prev = q;
      q->prev->next = q;
      q = p;
    }
  }
  while (p->prev)
    p = p->prev;
  return p;
}

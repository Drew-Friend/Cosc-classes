void list::push_front(const int &din)
{
    node *p = new node(din);
    p->next = head->next;
    head->next = p;
    N++;
}
void list::pop_front()
{
    node *p = head->next->next;
    delete head->next;
    head->next = p;
    N--;
}
const int &list::front()
{
    if (head->next)
        return head->next->data;
    return nullptr;
}
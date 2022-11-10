list::node *list::findnode(int i)
{
    if (i == -1)
        return head;
    else if (i < (N / 2))
    {
        node *p = head->next;
        while (i--)
            p = p->next;
        return p;
    }
    else
    {
        node *p = head;
        for (int j = 0; j < N - i; j++)
            p = p->prev;
        return p;
    }
}
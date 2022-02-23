#ifndef STACK_H
#define STACK_H

class stack
{
    int *head;
    int count;

public:
    stack();
    ~stack() { delete head; }
    bool empty() { return count == 0; }
    int size() { return count; }
    const int &top() { return head[count - 1]; }
    void pop() { count--; }
    void push(const int &din);
};

stack::stack()
{
    count = 0;
    head = new int[10];
}

void stack::push(const int &din)
{
    head[count] = din;
    count++;
}

#endif
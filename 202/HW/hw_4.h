#ifndef STACK_H
#define STACK_H

class stack
{
    int *head;
    int count;

public:
    stack();
    bool empty() { return count == 0; }
    int size() { return count; }
    void pop() { count--; }
    const int &top() { return head[count - 1]; }
    ~stack();
    void push(const int &din);
};

stack::stack()
{
    count = 0;
    head = new int[10];
}

stack::~stack()
{
    while (!empty())
        pop();
}

void stack::push(const int &din)
{
    head[count] = din;
    count++;
}

#endif

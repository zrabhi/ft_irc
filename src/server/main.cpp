#include <iostream>
struct A
{
    int a;
    virtual ~A()
    {};
};

struct B
{
    int b;
    virtual ~B()
    {};
};

struct D : public A, public B
{}; 

int main()
{
    D d;

    D *d_ptr = &d;
    void *p = (char  *)d_ptr + sizeof(A);
    B *b_ptr = (B*)(&d);

    std::cout << b_ptr << "\n" << p << std::endl; 

}

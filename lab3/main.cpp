#include "lab3.h"

using namespace std;

int main()
{
    STACK s(10);
    cout << s.size() << endl;
    return 0;
}

//初始化栈：最多存m个元素
STACK::STACK(int m) :
    // const 类型的常量只能用初始化列表
    elems(new int[m]),
    max(m)
{
    pos = 0;
}

//用栈s拷贝初始化栈
STACK::STACK(const STACK& s):
    // const 类型的常量只能用初始化列表
    elems(new int[s.max]),
    max(s.max)
{
    pos = s.pos;

//    逐个赋值
    int i;
    int *ip = elems, *is = s.elems;
    for(i=0; i< s.pos; i++)
        *(ip++) = *(is++);
}

STACK::~STACK()
{
    delete elems;
}

//返回栈的最大元素个数max
int STACK::size() const
{
    return max;
}

//返回栈的最大元素个数max
virtual int  size ( ) const
{

}

//返回栈的实际元素个数pos
virtual operator int ( ) const
{

}

//取下标x处的栈元素，第1个元素x=0
virtual int operator[ ] (int x) const
{

}

//将e入栈,并返回栈
virtual STACK& operator<<(int e)
{

}

//出栈到e,并返回栈
virtual STACK& operator>>(int &e)
{

}

//赋s给栈,并返回被赋值的栈
virtual STACK& operator=(const STACK&s)
{

}

//打印栈
virtual void print( ) const
{

}


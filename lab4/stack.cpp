#include "lab4.h"
using namespace std;

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
    // 防止重复析构
    if(elems == NULL) return;
    // 必须要用[]在前面，否则只是释放了
    delete []elems;
    *((int **)&elems) = NULL;
}

//返回栈的最大元素个数max
int STACK::size() const
{
    return max;
}


//返回栈的实际元素个数pos
STACK::operator int ( ) const
{
    return pos;
}

//取下标x处的栈元素，第1个元素x=0
int STACK::operator[ ] (int x) const
{
    if(x >= max)
        return -1;
    return elems[x];
}

//将e入栈,并返回栈
STACK& STACK::operator<<(int e)
{
    //检测是否栈满
    if(pos == max)
        return *this;
    // 入栈
    elems[pos++] = e;
    return *this;
}

//出栈到e,并返回栈
STACK& STACK::operator>>(int &e)
{
    //检测是否栈空
    if(pos == 0)
        return *this;
    // 出栈
    e = elems[--pos];
    return *this;
}

//赋s给栈,并返回被赋值的栈
STACK& STACK::operator=(const STACK&s)
{
    //先清空改指针指向的数据
    delete []elems;
    //const 可以通过强制类型转换来赋值
    // 取地址强制转换再转换回来
    *((int **)&elems) = new int [s.max];
    //同理max
    *((int *)&max) = s.max;
    this->pos = s.pos;
    //赋值
    for(int i = 0; i < s.pos; i++)
    {
        this->elems[i] = s.elems[i];
    }
    return *this;
}

//打印栈
void STACK::print( ) const
{
    int i;
    for(i=0; i<pos; i++)
        cout<< "  " <<elems[i];
}

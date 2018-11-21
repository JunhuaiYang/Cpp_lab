#include "lab4.h"
using namespace std;

//初始化队列
//使用两个栈，一个入队栈和一个出队栈
//继承到的为入队栈，s2为出队栈
QUEUE::QUEUE(int m) :
    STACK(m),
    s2(m)
{
}

//用队列s拷贝初始化队列
QUEUE::QUEUE(const QUEUE&s) :
    STACK(s),
    s2(s.s2)
{
}

//销毁队列
QUEUE::~QUEUE( )
{
    //s2会被自动调用delete
    this->~STACK();
}

//返回队列的实际元素个数
QUEUE::operator int ( ) const
{
    //父类函数的运算符重载只能用显示调用
    return STACK::operator int() + s2;
}

//返回队列是否已满，满返回1，否则返回0
int QUEUE::full ( ) const
{
    //判断出队栈s2是否为空
    //当不为空时，入队栈满即队满
    if( s2 > 0)
    {
        if(size() == STACK::operator int())
            return 1;
    }
    //其他情况
    return 0;
}

//取下标为x的元素，第1个元素下标为0
int QUEUE::operator[ ](int x)const
{
    // 入队栈正序
    // 出队栈倒序
    //出队栈在前
    if(x < s2)
    {
        //倒序
        return s2[s2-x-1];
    }
    else if(x-s2 < STACK::operator int())
    {
        return STACK::operator[](x-s2);
    }
    else
        return -1;

}

//将e入队列,并返回队列
QUEUE& QUEUE::operator<<(int e)
{
    // 入队思想
    //判断入堆是否已满
    if(size() != STACK::operator int())
    {
        //直接进入入队栈
        STACK::operator<<(e);
    }
    else
    {
        // 判断出队栈是否有元素
        if( s2 == 0)
        {
            //没有则将入队栈中的所有元素出栈到出队栈
            for(int i = 0; i <= size(); i++ )
            {
                int x;
                STACK::operator >> (x);
                s2 << x;
            }
            //进入入队栈
            STACK::operator<<(e);
        }
    }
    // 其他情况均无法入栈
    return *this;
}

//出队列到e,并返回队列
QUEUE& QUEUE::operator>>(int &e)
{
    //出队思想
    //先看出队栈是否有元素
    if( s2 > 0 )
    {
        // 直接出队
        s2 >> e;
    }
    else
    {
        // 如果入队栈不为0，则将入队栈出到出队栈
        if( STACK::operator int() > 0)
        {
            int s = STACK::operator int();
            for(int i = 0; i<s; i++)
            {
                int x;
                STACK::operator>>(x);
                s2 << x;
            }
            //再出栈
            s2 >> e;
        }
    }
    // 其他情况均不行
    return *this;

}

//赋s给队列,并返回被赋值的队列
QUEUE& QUEUE::operator=(const QUEUE&s)
{
    //通过类型转换使之调用父类的重载函数
    STACK::operator=(s);

    //赋值s2
    s2 = s.s2;

    return *this;
}

//打印队列
void QUEUE::print( ) const
{
    for(int i=0; i<(STACK::operator int() + s2); i++ )
        cout << "  " << (*this)[i] ;
}


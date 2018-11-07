#ifndef LAB2_H_INCLUDED
#define LAB2_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

class STACK
{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);		//初始化栈：最多m个元素
    STACK(const STACK&s); //用栈s拷贝初始化栈
    int  size ( ) const;		//返回栈的最大元素个数max
    int  howMany ( ) const;	//返回栈的实际元素个数pos
    int  getelem (int x) const;	//取下标x处的栈元素
    STACK& push(int e); 	//将e入栈,并返回栈
    STACK& pop(int &e); 	//出栈到e,并返回栈
    STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
    void print( ) const;		//打印栈
    ~STACK( );				//销毁栈
};




#endif // LAB2_H_INCLUDED

#include "lab3.h"

using namespace std;

int main()
{
    STACK s(10);
    cout << s.size() << endl;
    return 0;
}

//��ʼ��ջ������m��Ԫ��
STACK::STACK(int m) :
    // const ���͵ĳ���ֻ���ó�ʼ���б�
    elems(new int[m]),
    max(m)
{
    pos = 0;
}

//��ջs������ʼ��ջ
STACK::STACK(const STACK& s):
    // const ���͵ĳ���ֻ���ó�ʼ���б�
    elems(new int[s.max]),
    max(s.max)
{
    pos = s.pos;

//    �����ֵ
    int i;
    int *ip = elems, *is = s.elems;
    for(i=0; i< s.pos; i++)
        *(ip++) = *(is++);
}

STACK::~STACK()
{
    delete elems;
}

//����ջ�����Ԫ�ظ���max
int STACK::size() const
{
    return max;
}

//����ջ�����Ԫ�ظ���max
virtual int  size ( ) const
{

}

//����ջ��ʵ��Ԫ�ظ���pos
virtual operator int ( ) const
{

}

//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
virtual int operator[ ] (int x) const
{

}

//��e��ջ,������ջ
virtual STACK& operator<<(int e)
{

}

//��ջ��e,������ջ
virtual STACK& operator>>(int &e)
{

}

//��s��ջ,�����ر���ֵ��ջ
virtual STACK& operator=(const STACK&s)
{

}

//��ӡջ
virtual void print( ) const
{

}


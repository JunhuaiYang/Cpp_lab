#include "lab4.h"
using namespace std;

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
    // ��ֹ�ظ�����
    if(elems == NULL) return;
    // ����Ҫ��[]��ǰ�棬����ֻ���ͷ���
    delete []elems;
    *((int **)&elems) = NULL;
}

//����ջ�����Ԫ�ظ���max
int STACK::size() const
{
    return max;
}


//����ջ��ʵ��Ԫ�ظ���pos
STACK::operator int ( ) const
{
    return pos;
}

//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
int STACK::operator[ ] (int x) const
{
    if(x >= max)
        return -1;
    return elems[x];
}

//��e��ջ,������ջ
STACK& STACK::operator<<(int e)
{
    //����Ƿ�ջ��
    if(pos == max)
        return *this;
    // ��ջ
    elems[pos++] = e;
    return *this;
}

//��ջ��e,������ջ
STACK& STACK::operator>>(int &e)
{
    //����Ƿ�ջ��
    if(pos == 0)
        return *this;
    // ��ջ
    e = elems[--pos];
    return *this;
}

//��s��ջ,�����ر���ֵ��ջ
STACK& STACK::operator=(const STACK&s)
{
    //����ո�ָ��ָ�������
    delete []elems;
    //const ����ͨ��ǿ������ת������ֵ
    // ȡ��ַǿ��ת����ת������
    *((int **)&elems) = new int [s.max];
    //ͬ��max
    *((int *)&max) = s.max;
    this->pos = s.pos;
    //��ֵ
    for(int i = 0; i < s.pos; i++)
    {
        this->elems[i] = s.elems[i];
    }
    return *this;
}

//��ӡջ
void STACK::print( ) const
{
    int i;
    for(i=0; i<pos; i++)
        cout<< "  " <<elems[i];
}

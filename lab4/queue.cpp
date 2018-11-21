#include "lab4.h"
using namespace std;

//��ʼ������
//ʹ������ջ��һ�����ջ��һ������ջ
//�̳е���Ϊ���ջ��s2Ϊ����ջ
QUEUE::QUEUE(int m) :
    STACK(m),
    s2(m)
{
}

//�ö���s������ʼ������
QUEUE::QUEUE(const QUEUE&s) :
    STACK(s),
    s2(s.s2)
{
}

//���ٶ���
QUEUE::~QUEUE( )
{
    //s2�ᱻ�Զ�����delete
    this->~STACK();
}

//���ض��е�ʵ��Ԫ�ظ���
QUEUE::operator int ( ) const
{
    //���ຯ�������������ֻ������ʾ����
    return STACK::operator int() + s2;
}

//���ض����Ƿ�������������1�����򷵻�0
int QUEUE::full ( ) const
{
    //�жϳ���ջs2�Ƿ�Ϊ��
    //����Ϊ��ʱ�����ջ��������
    if( s2 > 0)
    {
        if(size() == STACK::operator int())
            return 1;
    }
    //�������
    return 0;
}

//ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
int QUEUE::operator[ ](int x)const
{
    // ���ջ����
    // ����ջ����
    //����ջ��ǰ
    if(x < s2)
    {
        //����
        return s2[s2-x-1];
    }
    else if(x-s2 < STACK::operator int())
    {
        return STACK::operator[](x-s2);
    }
    else
        return -1;

}

//��e�����,�����ض���
QUEUE& QUEUE::operator<<(int e)
{
    // ���˼��
    //�ж�����Ƿ�����
    if(size() != STACK::operator int())
    {
        //ֱ�ӽ������ջ
        STACK::operator<<(e);
    }
    else
    {
        // �жϳ���ջ�Ƿ���Ԫ��
        if( s2 == 0)
        {
            //û�������ջ�е�����Ԫ�س�ջ������ջ
            for(int i = 0; i <= size(); i++ )
            {
                int x;
                STACK::operator >> (x);
                s2 << x;
            }
            //�������ջ
            STACK::operator<<(e);
        }
    }
    // ����������޷���ջ
    return *this;
}

//�����е�e,�����ض���
QUEUE& QUEUE::operator>>(int &e)
{
    //����˼��
    //�ȿ�����ջ�Ƿ���Ԫ��
    if( s2 > 0 )
    {
        // ֱ�ӳ���
        s2 >> e;
    }
    else
    {
        // ������ջ��Ϊ0�������ջ��������ջ
        if( STACK::operator int() > 0)
        {
            int s = STACK::operator int();
            for(int i = 0; i<s; i++)
            {
                int x;
                STACK::operator>>(x);
                s2 << x;
            }
            //�ٳ�ջ
            s2 >> e;
        }
    }
    // �������������
    return *this;

}

//��s������,�����ر���ֵ�Ķ���
QUEUE& QUEUE::operator=(const QUEUE&s)
{
    //ͨ������ת��ʹ֮���ø�������غ���
    STACK::operator=(s);

    //��ֵs2
    s2 = s.s2;

    return *this;
}

//��ӡ����
void QUEUE::print( ) const
{
    for(int i=0; i<(STACK::operator int() + s2); i++ )
        cout << "  " << (*this)[i] ;
}


#include "lab3.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //�ַ�������
    char name[50];
    char* ctemp;
    strcpy(name, argv[0]);
    ctemp = strtok(name, ".");
    strcpy(name, ctemp);
    strcat( name, ".TXT");

    // ����ض���
    //������ļ�
    ofstream outf(name);
    //�ض���cout������ļ�
    cout.rdbuf( outf.rdbuf() );

    //�����������
    int commend[20];  //��������λ��
    int i, j, *pcomm = commend, icomm = 0;
    for(i=1; i<argc; i++)
    {
        if(*(argv[i]) == '-')
        {
            *pcomm = i;
            icomm++;
            pcomm++;
        }
    }

    int input, flag = 1, k;

    STACK *pstack = NULL, *temp;

    for(i=0; i<icomm && flag; i++)
    {
        switch (*(argv[commend[i]]+1))
        {
        // �趨ջ��С
        case 'S':
            input = atoi(argv[commend[i]+1]);
            if(input)
            {
                pstack = new STACK(input);
                cout << "S  " << input;
            }
            break;

        // ��ջ
        case 'I':
            if(pstack)
            {
                j = commend[i]+1 ;
                cout << "  I";
                while ( j<=argc-1 &&  *(argv[j]) != '-')  //��������
                {
                    input = atoi(argv[j]);
                    if(input)
                    {
                        //ֻ���������ж��Ƿ�ջ��
                        if( pstack->size() == *pstack)
                        {
                            flag = 0;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            *pstack << input;
                        }
                    }
                    j++;
                }
                if(flag)
                    pstack->print();
                else
                    cout << "  E" ;
            }
            break;

        // ��ջ
        case 'O':
            if(pstack)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  O";
                //�ж��Ƿ���Գ�ջ
                if(*pstack >= input)
                {
                    for(j=0; j<input; j++)
                    {
                        *pstack >> k;
                    }
                    pstack->print();
                }
                else
                {
                    cout << "  E" ;
                    flag = 0;
                }
            }
            break;

        // �������
        case 'C':
            if(pstack)
            {
                cout << "  C" ;
                temp = new STACK(*pstack);
                // ����ԭ��pstackָ���ջ
                delete pstack;
                pstack = temp;
                pstack->print();
            }
            break;

        // �����ֵ
        case 'A':
            if(pstack)
            {
                cout << "  A";
                input = atoi(argv[commend[i]+1]);
                temp = new STACK(input);
                // ���������
                *temp = *pstack;
                // ����ԭ��pstackָ���ջ
                delete pstack;
                pstack = temp;
                pstack->print();
            }
            break;

        // ջ��ʣ��Ԫ�ظ���
        case 'N':
            if(pstack)
            {
                cout << "  N";
                cout << "  " << *pstack;
            }
            break;

        case 'G':
            if(pstack)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  G";
                if((k = (*pstack)[input] ) != -1)
                    cout << "  " << k;
                else
                {
                    cout << "  E";
                    flag = 0;
                }
            }
            break;

        default:
            break;

        }
    }
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
    delete []elems;
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


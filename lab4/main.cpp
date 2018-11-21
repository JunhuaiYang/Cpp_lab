#include "lab4.h"

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

    // ����cout��������ָ��
    streambuf* coutBuf = cout.rdbuf();
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

    QUEUE *pqueue = NULL, *temp;

    for(i=0; i<icomm && flag; i++)
    {
        switch (*(argv[commend[i]]+1))
        {
        // �趨ջ��С
        case 'S':
            input = atoi(argv[commend[i]+1]);
            if(input)
            {
                pqueue = new QUEUE(input);
                cout << "S  " << input;
            }
            break;

        // ��ջ
        case 'I':
            if(pqueue)
            {
                j = commend[i]+1 ;
                cout << "  I";
                while ( j<=argc-1 &&  *(argv[j]) != '-')  //��������
                {
                    // Ŀǰû��ʲô�õİ취�ж�  ��0�� �ͷǷ��ַ�
                    // ֻ���ñ�־ǿ���ж�
                    int i_0 = 0;
                    if(*argv[j] == '0')
                        i_0 = 1;
                    input = atoi(argv[j]);
                    if(input || i_0)
                    {
                        //ֻ���������ж��Ƿ���
                        if( pqueue->full() )
                        {
                            flag = 0;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            *pqueue << input;
                        }
                    }
                    j++;
                }
                if(flag)
                    pqueue->print();
                else
                    cout << "  E" ;
            }
            break;

        // ��ջ
        case 'O':
            if(pqueue)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  O";
                //�ж��Ƿ���Գ���
                if(*pqueue >= input)
                {
                    for(j=0; j<input; j++)
                    {
                        *pqueue >> k;
                    }
                    pqueue->print();
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
            if(pqueue)
            {
                cout << "  C" ;
                temp = new QUEUE(*pqueue);
                // ����ԭ��pqueueָ���ջ
                delete pqueue;
                pqueue = temp;
                pqueue->print();
            }
            break;

        // �����ֵ
        case 'A':
            if(pqueue)
            {
                cout << "  A";
                input = atoi(argv[commend[i]+1]);
                temp = new QUEUE(input);
                // ���������
                *temp = *pqueue;
                // ����ԭ��pqueueָ���ջ
                delete pqueue;
                pqueue = temp;
                pqueue->print();
            }
            break;

        // ������ʣ��Ԫ�ظ���
        case 'N':
            if(pqueue)
            {
                cout << "  N";
                cout << "  " << *pqueue;
            }
            break;

        case 'G':
            if(pqueue)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  G";
                if((k = (*pqueue)[input] ) != -1)
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
    delete pqueue;  //�ͷ�
    //Ҫ�ر��ļ������
    outf.flush();
    outf.close();
    // �ָ�coutԭ������������ָ��
    // ���ָ��ᵼ�³����쳣�˳�
    cout.rdbuf(coutBuf);
    return 0;
}


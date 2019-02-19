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

    if(argc == 1)
    {
        int M, F, m, f;
        // ���������⡣
        cout << "*******************************************"<<endl;
        cout << "             �������                  " << endl;
        cout << "*******************************************"<<endl << endl;
        cout << "��������Ů���ӵĳ�ʼ����M��F, ��7  11" <<endl;
        cin >> M >> F;
        //�ж��Ƿ�Ϊ����
        if(!isPrime(M))
        {
            cout << "M��Ϊ������"<<endl;
            return 0;
        }
        if(!isPrime(F))
        {
            cout << "F��Ϊ������"<<endl;
            return 0;
        }
        if(M==F)
        {
            cout << "M Ӧ�ò�����F" << endl;
            return 0;
        }
        cout << "��������ʿ��Ůʿ m �� f����2  3" << endl;
        cin >> m >> f;
        if( (m<=0||m>M) || (f<=0||f>F) )
        {
            cout << "���벻����Ҫ��" << endl;
            return 0;
        }

        //�����Ų���ʼ�����ж���
        QUEUE MALE(M);
        QUEUE FEMALE(F);
        for(int i = 1; i<=M; i++)
        {
            MALE << i;
        }
        for(int i = 1; i<=F; i++)
        {
            FEMALE << i;
        }

        // ��ʼ�Ŷ�
        int tm = 0, tf = 0, count = 0;
        do
        {
            MALE >> tm;
            FEMALE >> tf;
            MALE << tm;
            FEMALE << tf;
            count++;
        }while(tm!=m || tf!=f);
        cout << "��֪�ڵ�" << count << "֧����ʱ����������"<<endl;
        getchar();
        getchar();
        return 0;
    }

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

// �ж�����
bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n);i++)
	{
        if (n%i == 0)
            return false;
	}
	return true;
}


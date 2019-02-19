#include "lab4.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //字符串处理
    char name[50];
    char* ctemp;
    strcpy(name, argv[0]);
    ctemp = strtok(name, ".");
    strcpy(name, ctemp);
    strcat( name, ".TXT");

    if(argc == 1)
    {
        int M, F, m, f;
        // 解决舞伴问题。
        cout << "*******************************************"<<endl;
        cout << "             舞伴问题                  " << endl;
        cout << "*******************************************"<<endl << endl;
        cout << "请输入男女两队的初始人数M和F, 如7  11" <<endl;
        cin >> M >> F;
        //判断是否为质数
        if(!isPrime(M))
        {
            cout << "M不为质数！"<<endl;
            return 0;
        }
        if(!isPrime(F))
        {
            cout << "F不为质数！"<<endl;
            return 0;
        }
        if(M==F)
        {
            cout << "M 应该不等于F" << endl;
            return 0;
        }
        cout << "请输入男士和女士 m 和 f，如2  3" << endl;
        cin >> m >> f;
        if( (m<=0||m>M) || (f<=0||f>F) )
        {
            cout << "输入不符合要求！" << endl;
            return 0;
        }

        //将其编号并初始化队列对象
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

        // 开始排队
        int tm = 0, tf = 0, count = 0;
        do
        {
            MALE >> tm;
            FEMALE >> tf;
            MALE << tm;
            FEMALE << tf;
            count++;
        }while(tm!=m || tf!=f);
        cout << "可知在第" << count << "支舞曲时可以遇到。"<<endl;
        getchar();
        getchar();
        return 0;
    }

    // 保存cout流缓冲区指针
    streambuf* coutBuf = cout.rdbuf();
    // 输出重定向
    //打开输出文件
    ofstream outf(name);
    //重定向cout输出到文件
    cout.rdbuf( outf.rdbuf() );

    //输入参数处理
    int commend[20];  //保存命令位置
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
        // 设定栈大小
        case 'S':
            input = atoi(argv[commend[i]+1]);
            if(input)
            {
                pqueue = new QUEUE(input);
                cout << "S  " << input;
            }
            break;

        // 入栈
        case 'I':
            if(pqueue)
            {
                j = commend[i]+1 ;
                cout << "  I";
                while ( j<=argc-1 &&  *(argv[j]) != '-')  //不是命令
                {
                    // 目前没有什么好的办法判断  “0” 和非法字符
                    // 只能用标志强行判断
                    int i_0 = 0;
                    if(*argv[j] == '0')
                        i_0 = 1;
                    input = atoi(argv[j]);
                    if(input || i_0)
                    {
                        //只能在外面判断是否满
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

        // 出栈
        case 'O':
            if(pqueue)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  O";
                //判读是否可以出队
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

        // 深拷贝构造
        case 'C':
            if(pqueue)
            {
                cout << "  C" ;
                temp = new QUEUE(*pqueue);
                // 销毁原来pqueue指向的栈
                delete pqueue;
                pqueue = temp;
                pqueue->print();
            }
            break;

        // 深拷贝赋值
        case 'A':
            if(pqueue)
            {
                cout << "  A";
                input = atoi(argv[commend[i]+1]);
                temp = new QUEUE(input);
                // 运算符重载
                *temp = *pqueue;
                // 销毁原来pqueue指向的栈
                delete pqueue;
                pqueue = temp;
                pqueue->print();
            }
            break;

        // 队列中剩余元素个数
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
    delete pqueue;  //释放
    //要关闭文件输出流
    outf.flush();
    outf.close();
    // 恢复cout原来的流缓冲区指针
    // 不恢复会导致程序异常退出
    cout.rdbuf(coutBuf);
    return 0;
}

// 判断质数
bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n);i++)
	{
        if (n%i == 0)
            return false;
	}
	return true;
}


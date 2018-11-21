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


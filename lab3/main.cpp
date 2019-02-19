#include "lab3.h"
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

    STACK *pstack = NULL, *temp;

    for(i=0; i<icomm && flag; i++)
    {
        switch (*(argv[commend[i]]+1))
        {
        // 设定栈大小
        case 'S':
            input = atoi(argv[commend[i]+1]);
            if(input)
            {
                pstack = new STACK(input);
                cout << "S  " << input;
            }
            break;

        // 入栈
        case 'I':
            if(pstack)
            {
                j = commend[i]+1 ;
                cout << "  I";
                while ( j<=argc-1 &&  *(argv[j]) != '-')  //不是命令
                {
                    input = atoi(argv[j]);
                    if(input)
                    {
                        //只能在外面判断是否栈满
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

        // 出栈
        case 'O':
            if(pstack)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  O";
                //判读是否可以出栈
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

        // 深拷贝构造
        case 'C':
            if(pstack)
            {
                cout << "  C" ;
                temp = new STACK(*pstack);
                // 销毁原来pstack指向的栈
                delete pstack;
                pstack = temp;
                pstack->print();
            }
            break;

        // 深拷贝赋值
        case 'A':
            if(pstack)
            {
                cout << "  A";
                input = atoi(argv[commend[i]+1]);
                temp = new STACK(input);
                // 运算符重载
                *temp = *pstack;
                // 销毁原来pstack指向的栈
                delete pstack;
                pstack = temp;
                pstack->print();
            }
            break;

        // 栈中剩余元素个数
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
    delete pstack;
    //要关闭文件输出流
    outf.close();
    // 恢复cout原来的流缓冲区指针
    // 不恢复会导致程序异常退出
    cout.rdbuf(coutBuf);
    return 0;
}


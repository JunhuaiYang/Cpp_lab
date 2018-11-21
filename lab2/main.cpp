#include "lab2.h"

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
                        if( pstack->size() == pstack->howMany())
                        {
                            flag = 0;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            pstack->push(input);
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
                if(pstack->howMany() >= input)
                {
                    for(j=0; j<input; j++)
                    {
                        pstack->pop(k);
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
                temp->assign(*pstack);
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
                cout << "  " << pstack->howMany();
            }
            break;

        case 'G':
            if(pstack)
            {
                input = atoi(argv[commend[i]+1]);
                cout << "  G";
                if((k = pstack->getelem(input)) != -1)
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

//初始化栈：最多存m个元素
STACK::STACK(int m) :
    // const 类型的常量只能用初始化列表
    elems(new int[m]),
    max(m)
{
    pos = 0;
}

//用栈s拷贝初始化栈
STACK::STACK(const STACK& s):
    // const 类型的常量只能用初始化列表
    elems(new int[s.max]),
    max(s.max)
{
    pos = s.pos;

//    逐个赋值
    int i;
    int *ip = elems, *is = s.elems;
    for(i=0; i< s.pos; i++)
        *(ip++) = *(is++);
}

//销毁栈
STACK::~STACK()
{
    //必须要用[]在前面，否则只是释放了
    delete []elems;
}

//返回栈的最大元素个数max
int STACK::size() const
{
    return max;
}

//返回栈的实际元素个数pos
int  STACK::howMany ( ) const
{
    return pos;
}

//取下标x处的栈元素
int  STACK::getelem (int x) const
{
    //先判断一下
    if(x < 0 || x > pos-1)
        return -1;
    return elems[x];
}

//将e入栈,并返回栈
STACK& STACK::push(int e)
{
    //检测是否栈满
    if(pos == max)
        return *this;
    // 入栈
    elems[pos++] = e;
    return *this;
}

//出栈到e,并返回栈
STACK& STACK::pop(int &e)
{
    //检测是否栈空
    if(pos == 0)
        return *this;
    // 出栈
    e = elems[--pos];
    return *this;
}

//赋s给栈,并返回被赋值的栈
STACK& STACK::assign(const STACK&s)
{
    //先清空改指针指向的数据
    delete []elems;
    //const 可以通过强制类型转换来赋值
    // 取地址强制转换再转换回来
    *((int **)&elems) = new int [s.max];
    //同理max
    *((int *)&max) = s.max;
    this->pos = s.pos;
    //赋值
    for(int i = 0; i < s.pos; i++)
    {
        this->elems[i] = s.elems[i];
    }
    return *this;
}

//打印栈
void STACK::print( ) const
{
    int i;
    for(i=0; i<pos; i++)
        cout<< "  " <<elems[i];
}


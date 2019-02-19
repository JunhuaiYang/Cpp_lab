#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct STACK
{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
};

void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK_s(STACK *const p, const STACK &s); //用栈s初始化p指向的栈
int  size (const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany (const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem (const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

int main(int argc, char const *argv[])
{
    //字符串处理
    char name[50];
    char* ctemp;
    strcpy(name, argv[0]);
    ctemp = strtok(name, ".");
    strcpy(name, ctemp);
    strcat( name, ".TXT");
    // 输出重定向
    freopen(name, "w", stdout);

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
                pstack = (STACK*)malloc(sizeof(STACK));
                initSTACK(pstack, input);
                printf("S  %d", input);
            }
            break;

        // 入栈
        case 'I':
            if(pstack)
            {
                j = commend[i]+1 ;
                printf("  I");
                while ( j<=argc-1 &&  *(argv[j]) != '-')  //不是命令
                {
                    input = atoi(argv[j]);
                    if(input)
                    {
                        pstack = push(pstack, input);
                        if( pstack)
                            flag = 1;
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    j++;
                    //else flag = 0;
                }
                if(flag)
                    print(pstack);
                else
                    printf("  E");
            }
            break;

        // 出栈
        case 'O':
            if(pstack)
            {
                input = atoi(argv[commend[i]+1]);
                printf("  O");
                for(j=0; j<input && flag; j++)
                {
                    pstack = pop(pstack, k);
                    if(pstack)
                        flag = 1;
                    else
                        flag = 0;
                }
                if(flag)
                    print(pstack);
                else
                    printf("  E");
            }
            break;

        // 深拷贝构造
        case 'C':
            if(pstack)
            {
                printf("  C");
                temp = (STACK*)malloc(sizeof(STACK));
                initSTACK_s(temp, *pstack);
                // 销毁原来pstack指向的栈
                destroySTACK(pstack);
                pstack = temp;
                print(pstack);
            }
            break;

        // 深拷贝赋值
        case 'A':
            if(pstack)
            {
                printf("  A");
                input = atoi(argv[commend[i]+1]);
                temp = (STACK*)malloc(sizeof(STACK));
                initSTACK(temp, input);
                assign(temp, *pstack);
                // 销毁原来pstack指向的栈
                destroySTACK(pstack);
                pstack = temp;
                print(pstack);
            }
            break;

        // 栈中剩余元素个数
        case 'N':
            if(pstack)
            {
                printf("  N");
                printf("  %d", howMany(pstack));
            }
            break;

        case 'G':
            if(pstack)
            {
                input = atoi(argv[commend[i]+1]);
                printf("  G");
                if((k=getelem(pstack, input)) != -1)
                    printf("  %d", k);
                else
                {
                    printf("  E");
                    flag = 0;
                }
            }
            break;

        default:
            break;
        }

    }
    free(pstack);
    return 0;
}

//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, int m)
{
    p->elems = (int*)malloc(sizeof(int)*m);
    //内存分配失败
    if(!p->elems)
        exit(1);

    p->max = m;
    p->pos = 0;  //0表示栈空
}

// 重载？？
//用栈s初始化p指向的栈
//此时p未初始化
void initSTACK_s(STACK *const p, const STACK &s)
{
    //先初始化p的指向的栈
    initSTACK(p, s.max);

    p->pos = s.pos;

    //复制s栈内容
    int i;
    int *ip = p->elems, *is = s.elems;
    for(i=0; i< s.pos; i++)
        *(ip++) = *(is++);
}

//返回p指向的栈的最大元素个数max
int  size (const STACK *const p)
{
    return p->max;
}

//返回p指向的栈的实际元素个数pos
int  howMany (const STACK *const p)
{
    return p->pos;
}

//取下标x处的栈元素
int  getelem (const STACK *const p, int x)
{
    //先判断一下
    if(x < 0 || x > p->pos-1)
        return -1;
    return p->elems[x];
}

//将e入栈，并返回p
STACK *const push(STACK *const p, int e)
{
    //检测是否栈满
    if(p->pos == p->max)
        return NULL;
    // 入栈
    p->elems[p->pos++] = e;
    return p;
}

//出栈到e，并返回p
STACK *const pop(STACK *const p, int &e)
{
    //检测是否栈空
    if(p->pos == 0)
        return NULL;

    // 出栈
    e = p->elems[--p->pos];
    return p;
}

//赋s给p指的栈,并返回p
//此时p已经初始化
STACK *const assign(STACK*const p, const STACK &s)
{

    p->max = s.max;
    p->pos = s.pos;

    //使用realloc重新分配内存
    p->elems = (int*)realloc(p->elems, sizeof(int)*s.max);

    //复制s栈内容
    int i;
    int *ip = p->elems, *is = s.elems;
    for(i=0; i<s.pos; i++)
        *(ip++) = *(is++);

    return p;
}

//打印p指向的栈
void print(const STACK*const p)
{
    int i;
    for(i=0; i<p->pos; i++)
        printf("  %d", p->elems[i]);
}

//销毁p指向的栈
void destroySTACK(STACK*const p)
{
    free(p->elems);
    free(p);
}


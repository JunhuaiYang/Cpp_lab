#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct STACK
{
    int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
    int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};

void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK_s(STACK *const p, const STACK &s); //��ջs��ʼ��pָ���ջ
int  size (const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany (const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem (const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

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
    freopen(name, "w", stdout);

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
                pstack = (STACK*)malloc(sizeof(STACK));
                initSTACK(pstack, input);
                printf("S  %d", input);
            }
            break;

        // ��ջ
        case 'I':
            if(pstack)
            {
                j = commend[i]+1 ;
                printf("  I");
                while ( j<=argc-1 &&  *(argv[j]) != '-')  //��������
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

        // ��ջ
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

        // �������
        case 'C':
            if(pstack)
            {
                printf("  C");
                temp = (STACK*)malloc(sizeof(STACK));
                initSTACK_s(temp, *pstack);
                // ����ԭ��pstackָ���ջ
                destroySTACK(pstack);
                pstack = temp;
                print(pstack);
            }
            break;

        // �����ֵ
        case 'A':
            if(pstack)
            {
                printf("  A");
                input = atoi(argv[commend[i]+1]);
                temp = (STACK*)malloc(sizeof(STACK));
                initSTACK(temp, input);
                assign(temp, *pstack);
                // ����ԭ��pstackָ���ջ
                destroySTACK(pstack);
                pstack = temp;
                print(pstack);
            }
            break;

        // ջ��ʣ��Ԫ�ظ���
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

//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, int m)
{
    p->elems = (int*)malloc(sizeof(int)*m);
    //�ڴ����ʧ��
    if(!p->elems)
        exit(1);

    p->max = m;
    p->pos = 0;  //0��ʾջ��
}

// ���أ���
//��ջs��ʼ��pָ���ջ
//��ʱpδ��ʼ��
void initSTACK_s(STACK *const p, const STACK &s)
{
    //�ȳ�ʼ��p��ָ���ջ
    initSTACK(p, s.max);

    p->pos = s.pos;

    //����sջ����
    int i;
    int *ip = p->elems, *is = s.elems;
    for(i=0; i< s.pos; i++)
        *(ip++) = *(is++);
}

//����pָ���ջ�����Ԫ�ظ���max
int  size (const STACK *const p)
{
    return p->max;
}

//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  howMany (const STACK *const p)
{
    return p->pos;
}

//ȡ�±�x����ջԪ��
int  getelem (const STACK *const p, int x)
{
    //���ж�һ��
    if(x < 0 || x > p->pos-1)
        return -1;
    return p->elems[x];
}

//��e��ջ��������p
STACK *const push(STACK *const p, int e)
{
    //����Ƿ�ջ��
    if(p->pos == p->max)
        return NULL;
    // ��ջ
    p->elems[p->pos++] = e;
    return p;
}

//��ջ��e��������p
STACK *const pop(STACK *const p, int &e)
{
    //����Ƿ�ջ��
    if(p->pos == 0)
        return NULL;

    // ��ջ
    e = p->elems[--p->pos];
    return p;
}

//��s��pָ��ջ,������p
//��ʱp�Ѿ���ʼ��
STACK *const assign(STACK*const p, const STACK &s)
{

    p->max = s.max;
    p->pos = s.pos;

    //ʹ��realloc���·����ڴ�
    p->elems = (int*)realloc(p->elems, sizeof(int)*s.max);

    //����sջ����
    int i;
    int *ip = p->elems, *is = s.elems;
    for(i=0; i<s.pos; i++)
        *(ip++) = *(is++);

    return p;
}

//��ӡpָ���ջ
void print(const STACK*const p)
{
    int i;
    for(i=0; i<p->pos; i++)
        printf("  %d", p->elems[i]);
}

//����pָ���ջ
void destroySTACK(STACK*const p)
{
    free(p->elems);
    free(p);
}


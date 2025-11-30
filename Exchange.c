#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct stackNode
{
    ElemType data;
    struct stackNode* next;
}StackNode;

typedef struct queueNode
{
    ElemType data;
    struct queueNode* next;
}QueueNode;

typedef struct queue
{
    QueueNode* head;
    QueueNode* front;
    QueueNode* rear;
}Queue;

typedef struct stack
{
    StackNode* top;
}Stack;

Stack* S_initial()
{
    Stack* S = (Stack*)malloc(sizeof(Stack));
    S->top = NULL;
    return S;
}

void S_push(Stack* S,ElemType* e)
{
    StackNode* N = (StackNode*)malloc(sizeof(StackNode));
    N->data = *e;
    N->next = S->top;
    S->top = N;
}

int S_pop(Stack* S,ElemType* e)
{
    StackNode* p = S->top;
    if(p == NULL)
    {
        printf("Is Emepty!\n");
        return 1;
    }
    S->top = S->top->next;
    *e = p->data;
    free(p);
    p = NULL;
    return 0;
}

Queue* Q_initial()
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->head = (QueueNode*)malloc(sizeof(QueueNode));
    Q->head->data = 0;
    Q->head->next = NULL;
    Q->front = Q->head;
    Q->rear = Q->head;
    return Q;
}

void Q_push(Queue* Q,ElemType* e)
{
    QueueNode* N = (QueueNode*)malloc(sizeof(QueueNode));
    N->data = *e;
    N->next = NULL;
    Q->rear->next = N;
    Q->rear = N;
}

int Q_pop(Queue* Q,ElemType* e)
{
    QueueNode* p = Q->front->next;
    if(p == NULL)
    {
        printf("Is Emepty!\n");
        return 1;
    }
    *e = Q->front->next->data;
    Q->front->next = Q->front->next->next;
    return 0;
}

typedef enum countType
{
    Left_paren,Right_paren,ADD,SUB,MUL,DIV,NUM,EOM
}CountType;

char Tim[] = {"3+4*(5+2)+8-10/7"};

void tokenJudge(char C,CountType* Token)
{
    switch(C)
    {
        case '(' :
        *Token = Left_paren;
        break;
        case ')' :
        *Token = Right_paren;
        break;
        case '+' :
        *Token = ADD;
        break;
        case '-' :
        *Token = SUB;
        break;
        case '*' :
        *Token = MUL;
        break;
        case '/' :
        *Token = DIV;
        break;
        case '\0':
        *Token = EOM;
        break;
        default :
        *Token = NUM;
    }
}

void ExChange(char* Be,char* Now)
{
    CountType Token;
    int Out_level[] = {8,7,1,1,2,2,0,0};
    int In_level[] = {0,7,1,1,2,2,0,0};
    Stack* Buf = S_initial();
    ElemType zero = '(';
    S_push(Buf,&zero);
    Queue* Output = Q_initial();
    int Digit = 0;
    tokenJudge(Be[Digit],&Token);
    while(Token!=EOM)
    {
        if(Token == NUM)
        {
            Q_push(Output,&Be[Digit]);
        }
        if(Token == Right_paren)
        {
            while(Token != Left_paren)
            {
                ElemType Caght;
                S_pop(Buf,&Caght);
                tokenJudge(Caght,&Token);
                if(Token!=Left_paren&&Token!=Right_paren) Q_push(Output,&Caght);
            }
            Token = Right_paren;
        }
        if(Token == ADD)
        {
            ElemType Caght;
            S_pop(Buf,&Caght);
            tokenJudge(Caght,&Token);
            while(Out_level[ADD]<=In_level[Token])
            {
                Q_push(Output,&Caght);
                S_pop(Buf,&Caght);
                tokenJudge(Caght,&Token);
            }
            S_push(Buf,&Caght);
            S_push(Buf,&Be[Digit]);
            Token =ADD;
        }
        if(Token == SUB)
        {
            ElemType Caght;
            S_pop(Buf,&Caght);
            tokenJudge(Caght,&Token);
            while(Out_level[SUB]<=In_level[Token])
            {
                Q_push(Output,&Caght);
                S_pop(Buf,&Caght);
                tokenJudge(Caght,&Token);
            }
            S_push(Buf,&Caght);
            S_push(Buf,&Be[Digit]);
            Token = SUB;
        }
        if(Token == MUL)
        {
            ElemType Caght;
            S_pop(Buf,&Caght);
            tokenJudge(Caght,&Token);
            while(Out_level[MUL]<=In_level[Token])
            {
                Q_push(Output,&Caght);
                S_pop(Buf,&Caght);
                tokenJudge(Caght,&Token);
            }
            S_push(Buf,&Caght);
            S_push(Buf,&Be[Digit]);
            Token =MUL;
        }
        if(Token == DIV)
        {
            ElemType Caght;
            S_pop(Buf,&Caght);
            tokenJudge(Caght,&Token);
            while(Out_level[DIV]<=In_level[Token])
            {
                Q_push(Output,&Caght);
                S_pop(Buf,&Caght);
                tokenJudge(Caght,&Token);
            }
            S_push(Buf,&Caght);
            S_push(Buf,&Be[Digit]);
            Token = DIV;
        }
        if(Token ==  Left_paren)
        {
            S_push(Buf,&Be[Digit]);
        }
        Digit++;
        tokenJudge(Be[Digit],&Token);
    }
            if(Token == EOM)
        {
            ElemType O;
            for(;;)
            {
                int K =S_pop(Buf,&O);
                if(K==1) break;
                Q_push(Output,&O);
            }
            int Count=0;
            for( ; ; )
            {
                int J = Q_pop(Output,&O);
                if (J==1) break;
                Now[Count] = O;
                Count++;
            }
            Token = EOM;
        }
}

int main()
{
    char M[100]={0};
    ExChange(Tim,M);
    printf("%s",M);
    return 0;
}


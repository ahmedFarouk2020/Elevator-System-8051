/*                STACK BASED ARRAYS                 */
/*****************************************************/
#include "stack.h"
#include <stdio.h>

void creatStack(Stack* ptr_s)
{
    ptr_s->top = 0;
}

int push(StackEntry value , Stack* ptr_s)
{
    if(ptr_s->top == MAXSTACK)
        return 0;
    else    
    {
        ptr_s->entry[ptr_s->top++] = value ;
        return 1;
    }    
}


int StackFull(Stack* ptr_s)
{
    return((ptr_s->top == MAXSTACK));
}

int StackEmpty(Stack* ptr_s)
{
    return((ptr_s->top == 0));
}

void pop(StackEntry* pe , Stack* ptr_s)
{
    *pe = ptr_s->entry[-- ptr_s->top];
}

void clearStack(Stack* ptr_s)
{
    ptr_s->top = 0;
}


/************************************************************************************************/
/*                                   USER LEVEL                                                 */
/***********************************************************************************************/


int main()
{
    Stack s;
    StackEntry e;
    creatStack(&s);

    if(!StackFull(&s))      push(e , &s);
    if(!StackEmpty(&s))     pop(&e , &s);   

    return 0;
}
/*******************************************************/
/*                 SET DATA STRUCTURE                 */                
/*******************************************************/
#include "Headers/set.h"
#include <stdio.h>

u8 push_value(u8 value)
{
    if(index <= 9){    
        requests[index] = value;
        index++;
        return 1;
    }
    else{
        u8 counter = 0;
        for(counter; counter <= 9; counter++){
            if(requests[counter] == 0)
            {
                requests[counter] = value;
                return 1;
            }
        }
        return 0;
    }

}


u8 enqueue(u8 value)
{
    if(q_index <5){
        queue[q_index] = value;
        q_index++;
        return 1;
    }
    else{ return 0; }
}

u8 dequeue()
{
    u8 counter = 0;
    u8 poped_data;
    for(counter; counter <= 5; counter++){
        if(queue[counter] != 0)
        {
            poped_data = queue[counter];
            queue[counter] = 0;
            if(counter == 4)    {q_index = 0;}
            return poped_data;
        }
    }
    return 0;
}

/* 
 * returned Value = 1? value exists
 * returned Value = 0? value isn't exist
 */ 
u8 Is_value_exist(u8 value)
{
    u8 i = 0; // counter
    for(i; i <= 9; i++)
    {
        if(value == requests[i])
        {
            
            return i;
        }
    }
}

void remove_index(u8 index)
{
    requests[index] = 0;
}

void display(u8 arr[])
{
    u8 i = 0;
    for(;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main()
{
    index = 0;
    push_value(5);
    push_value(4);
    push_value(45);
    push_value(6);
    push_value(5);
    push_value(4);
    push_value(45);
    push_value(6);
    push_value(5);
    push_value(4);
    push_value(45);
    push_value(6);
    display(requests);
    remove_index(Is_value_exist(45));
    display(requests);

    enqueue(21);
    enqueue(1);
    enqueue(2);
    enqueue(98);
    enqueue(31);
    enqueue(200);
    display(queue);
    dequeue();  dequeue(); dequeue();  dequeue(); dequeue();  
    enqueue(100);
    display(queue);
    return 0;
}
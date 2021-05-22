

#define u8 int

u8 requests[4] = {0};
u8 index = 0;   // the place in array where the new value will be placed
u8 queue[2] = {0};
u8 q_index = 0; // the place in array where the new value will be placed
u8 q_size = 0;
/********************************/
/*          FUNCTIONS            */
/******************************/
u8 enqueue(u8 value)
{
    if (q_size == 0)
        q_index = 0;
    if (value == queue[0] || value == queue[1])
        return 0;
    if (q_index < 2)
    {
        queue[q_index] = value;
        q_index++;
        q_size++;
        return 1;
    }
    else
    {
        return 0;
    }
}

u8 dequeue()
{
    u8 counter = 0;
    u8 poped_data;
    for (counter; counter <= 5; counter++)
    {
        if (queue[counter] != 0)
        {
            poped_data = queue[counter];
            queue[counter] = 0;
            if (counter == 4)
            {
                q_index = 0;
            }
            q_size--;
            return poped_data;
        }
    }
    return 0;
}
u8 Is_value_exist(u8 value)
{
    u8 i = 0; // counter
    for(i; i <= 4; i++)
    {
        if(value == requests[i])
        {
            return 1;
        }
    }
    return 0;
}

u8 push_value(u8 value)
{
    if (Is_value_exist(value))
        return 0;
    
    if(index <= 4)
    {    
        requests[index] = value;
        index++;
        return 1;
    }
    else
    {
        u8 i;
        u8 j;
        for(i=0; i <= 4; i++)
        {
            if(requests[i] == 0)
            {
                requests[i] = value;
                return 1;
            }
        }
        for(i=0; i <= 4; i++)
        {
            for(j=0; j <= 4; j++)
            {
                
            }
        }
        return 0;
    }
}

/* 
 * returned Value = 1? value exists
 * returned Value = 0? value isn't exist
 */ 
void remove_value(u8 value)
{
    u8 i = 0;
    for(i; i <= 4; i++)
    {
        if(value == requests[i])
        {
            requests[i] = 0;
        }
    }
}

#include <stdio.h>
int main()
{
    // printf("%d \n",dequeue());
    push_value(1);
    push_value(2);
    push_value(4);
    push_value(3);

    // 1 3 4
    // remove_value()
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d \n", requests[i]);
    }
    
    // printf("%d \n",);
    // printf("%d \n",dequeue());
}

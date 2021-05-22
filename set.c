

#define u8 int

u8 requests[10] = {0};
u8 queue[2] = {0};
u8 index = 0;   // the place in array where the new value will be placed
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
#include <stdio.h>
int main()
{
    // printf("%d \n",dequeue());
    enqueue(9);
    enqueue(8);

    printf("%d \n",dequeue());
    printf("%d \n",dequeue());
}

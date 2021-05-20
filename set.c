/*******************************************************/
/*                 SET DATA STRUCTURE                 */                
/*******************************************************/
#include "set.h"
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

void display(void)
{
    u8 i = 0;
    for(;i<10;i++)
    {
        printf("%d ",requests[i]);
    }
    printf("\n");
}

// int main()
// {
//     index = 0;
//     push_value(5);
//     push_value(4);
//     push_value(45);
//     push_value(6);
//     push_value(5);
//     push_value(4);
//     push_value(45);
//     push_value(6);
//     push_value(5);
//     push_value(4);
//     push_value(45);
//     push_value(6);
//     display();
//     remove_index(Is_value_exist(45));
//     display();
//     return 0;
// }
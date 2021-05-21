// assume step angle = 45 so it needs 4 steps to complete 1 cycle
// assume the number of steps = 16 step to mave one completed floor
// assume rotating clockwise will make the elevator go up and anti-clockwise will go down
#include "../Headers/BIT_MATH.h"

void delay()
{
    unsigned int i;
    for (i = 0; i < 20000; i++)
    {
        continue;
    }
}
const NUMBER_OF_STEPS = 16; // we can change to the desire number

void elevate(unsigned int current_floor, unsigned int destination)
{
    // number of floors needed
    signed int floors_number = destination - current_floor;
    unsigned int i,j;
    unsigned int steps;
    // if (P3 == 0x00)
    // {
    //     return;
    // }
    if (floors_number > 0)
    {
        j = 4;
        // we will go up
        // number of steps to reach the destination
        // 0001 -> 0010 -> 0100 -> 1000 -> 0001 -> ...
        steps = NUMBER_OF_STEPS * (floors_number);
        // temp = P3
        // 0000 xxxx
        // 0001 1111
        P3 = 0x1f & P3;
        for (i = 1; i <= steps; i++)
        {
            if(i % NUMBER_OF_STEPS == 0)
                seven_segme
            
            // 0001 xxxx j=4 
            // 0010 xxxx j=5
            // 0100 xxxx j=6
            // 1000 xxxx j=7

            
            
            if (j == 7)
            {
                CLR_BIT(P3, j);
                j = 4;
                SET_BIT(P3, j);  //0001 xxxx j=4
            }
            else
            {
                CLR_BIT(P3, j);
                j++;
                SET_BIT(P3, j);  //0001 xxxx j=4
            }
            //0001 xxxx j=5
            delay();
        }
        P3 = 0x0f & P3;
    }
    else if (floors_number < 0)
    {
        j = 7;
        // we will go down
        // number of steps to reach the destination
        // 1000 -> 0100 -> 0010 -> 0001 -> 1000 -> ...
        steps = NUMBER_OF_STEPS * (floors_number * (-1));
        P3 = 0x0f & P3; // 1000 xxxx
        for (i = 0; i < steps; i++)
        {
            if (j == 4)
            {
                CLR_BIT(P3, j);
                j = 7;
                SET_BIT(P3, j);  //0001 xxxx j=4
            }
            else
            {
                CLR_BIT(P3, j);
                j--;
                SET_BIT(P3, j);  //0001 xxxx j=4
            }
            //0001 xxxx j=5
            delay();
        }
        P3 = 0x0f & P3;
    }
}
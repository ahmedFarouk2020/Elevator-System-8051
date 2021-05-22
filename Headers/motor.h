#ifndef __MOTOR_H
#define __MOTOR_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "delay.h"

#define NUMBER_OF_STEPS 16

void seven_segment(u8 floor_num)
{
    switch (floor_num)
    {
    case 0:
        P1 = 0x3F;
        break;
    case 1:
        P1 = 0x06;
        break;
    case 2:
        P1 = 0x5b;
        break;
    case 3:
        P1 = 0x4f;
        break;
    case 4:
        P1 = 0x66;
        break;
    }
}

// assume step angle = 45 so it needs 4 steps to complete 1 cycle
// assume the number of steps = 16 step to mave one completed floor
// assume rotating clockwise will make the elevator go up and anti-clockwise will go down
void elevate(u8 *current_floor, u8 destination)
{
    // number of floors needed
    signed int floors_number = destination - *current_floor;
    unsigned int i, j;
    unsigned int steps;

    if (floors_number > 0)
    {
        j = 4;
        // we will go up
        // number of steps to reach the destination
        // 0001 -> 0010 -> 0100 -> 1000 -> 0001 -> ...
        steps = NUMBER_OF_STEPS * (floors_number);

        P3 = 0x1f & P3;
        for (i = 1; i <= steps; i++)
        {
            if (i % NUMBER_OF_STEPS == 0)
            {
                (*current_floor)++;
                seven_segment(*current_floor);
            }

            if (j == 7)
            {
                CLR_BIT(P3, j);
                j = 4;
                SET_BIT(P3, j); //0001 xxxx j=4
            }
            else
            {
                CLR_BIT(P3, j);
                j++;
                SET_BIT(P3, j); //0001 xxxx j=4
            }
            //0001 xxxx j=5
            Delay_MS(100);
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
        for (i = 1; i <= steps; i++)
        {

            if (i % NUMBER_OF_STEPS == 0)
            {
                (*current_floor)--;
                seven_segment(*current_floor);
            }

            if (j == 4)
            {
                CLR_BIT(P3, j);
                j = 7;
                SET_BIT(P3, j); //0001 xxxx j=4
            }
            else
            {
                CLR_BIT(P3, j);
                j--;
                SET_BIT(P3, j); //0001 xxxx j=4
            }
            Delay_MS(100);
        }
        P3 = 0x0f & P3;
    }
}

#endif
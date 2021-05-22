#include "C8051F020.h"
#include "Headers/BIT_MATH.h"
#include "Headers/STD_TYPES.h"
#include "Headers/motor.h"
#include "Headers/delay.h"

#define GROUND_FLOOR 10
#define TOP_FLOOR 4

u8 CURRENT_FLOOR = 0; //GROUND
u8 queue[2] = {0};
u8 q_index = 0; // the place in array where the new value will be placed
u8 q_size = 0;

void go_to_floor(u8 *current_floor, u8 destination)
{
    CLR_BIT(P3, 0);
    elevate(current_floor, destination);
    SET_BIT(P3, 0);
    Delay_MS(1000);
}

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

int main()
{
    u8 floor = 0;
    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock

    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x14;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled

    IT0 = 1; // Configure interrupt 0 for falling edge on INT0
    EX0 = 1; // Enabling the EX0 interrupt
    // PX0 = 0;
    IT1 = 1; // Configure interrupt 1 for falling edge on INT0
    EX1 = 1; // Enabling the EX1 interrupt
    PX1 = 1; // Priority
    EA = 1;  // Enabling the global interrupt flag

    P2MDOUT = 0xff;
    P1MDOUT = 0xff; //seven segment
    P1 = 0x00;      //seven segment

    // 01111111
    P2 = 0x7f; //CONTROL_PORTS
    CLR_BIT(P3, 0);
    seven_segment(CURRENT_FLOOR);
    while (1)
    {
        if (q_size == 0)
        {
            continue;
        }

        floor = dequeue();
        if (floor == GROUND_FLOOR)
        {
            go_to_floor(&CURRENT_FLOOR, 0);
        }
        else if (floor == TOP_FLOOR)
        {
            go_to_floor(&CURRENT_FLOOR, TOP_FLOOR);
        }
    }
    return 0;
}

void request(void) interrupt 0
{
    if (!GET_BIT(P2, 2))
    {
        // Ground
        if (CURRENT_FLOOR != 0)
        {
            go_to_floor(&CURRENT_FLOOR, 0);
        }
    }
    else if (!GET_BIT(P2, 3))
    {
        // floor 1
        if (CURRENT_FLOOR != 1)
        {
            go_to_floor(&CURRENT_FLOOR, 1);
        }
    }
    else if (!GET_BIT(P2, 4))
    {
        // floor 2
        if (CURRENT_FLOOR != 2)
        {
            go_to_floor(&CURRENT_FLOOR, 2);
        }
    }
    else if (!GET_BIT(P2, 5))
    {
        // floor 3
        if (CURRENT_FLOOR != 3)
        {
            go_to_floor(&CURRENT_FLOOR, 3);
        }
    }
    else if (!GET_BIT(P2, 6))
    {
        // floor 4
        if (CURRENT_FLOOR != 4)
        {
            go_to_floor(&CURRENT_FLOOR, 4);
        }
    }
}

void request2(void) interrupt 2
{
    if (!GET_BIT(P2, 1))
    {
        if (CURRENT_FLOOR != 0)
            enqueue(GROUND_FLOOR);
    }
    if (!GET_BIT(P2, 0))
    {
        if (CURRENT_FLOOR != 4)
            enqueue(TOP_FLOOR);
    }
}
#include "C8051F020.h"
#include "Headers/BIT_MATH.h"
#include "Headers/STD_TYPES.h"
#include "Headers/motor.h"
#include "Headers/delay.h"

#define GROUND_FLOOR 0
#define TOP_FLOOR 4

u8 NEXT_FLOOR;
u8 CURRENT_FLOOR = 0; //GROUND
u8 pending_requests[5] = {5, 5, 5, 5, 5};
u8 pending_requests_index = 0; // the place in array where the new value will be placed
u8 requests[5] = {5, 5, 5, 5, 5};
u8 requests_index = 0; // the place in array where the new value will be placed
u8 queue[2] = {5,5};
u8 q_index = 0; // the place in array where the new value will be placed
u8 q_size = 0;
s8 direction = 1;

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
    for (counter; counter <= 1; counter++)
    {
        if (queue[counter] != 5)
        {
            poped_data = queue[counter];
            queue[counter] = 5;
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

/* 
 * returned Value = 1? value exists
 * returned Value = 0? value isn't exist
 */
u8 Is_value_exist(u8 *arr, u8 value)
{
    u8 i = 0; // counter
    for (i; i <= 4; i++)
    {
        if (value == arr[i])
        {
            return 1;
        }
    }
    return 0;
}

void sort(u8 *array, u8 size)
{
    u8 ordered;
    u8 i = 0;
    u8 j = 0;
    u8 temp;

    for (i = 0; i < size - 1; i++)
    {
        ordered = 1;

        for (j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                ordered = 0;
            }
        }

        if (ordered)
            break;
    }
    if (direction == -1)
    {
        for (i = 0; i < 5; i++)
        {
            if (requests[i] == 5)
            {
                NEXT_FLOOR = i - 1;
                break;
            }
        }
    }
    // Delay_MS(2000);
}

void push_value(u8 *arr, u8 *idx, u8 value)
{
    if (Is_value_exist(arr, value))
        return;

    if (*idx <= 4)
    {
        arr[*idx] = value;
        (*idx)++;
    }
    else
    {
        u8 counter = 0;
        for (counter; counter <= 4; counter++)
        {
            if (arr[counter] == 5)
            {
                arr[counter] = value;
            }
        }
    }
    sort(arr, 5);
}

u8 pop(u8 *arr, u8 idx)
{
    u8 popped_value = arr[idx];
    arr[idx] = 5;
    sort(arr, 5);

    return popped_value;
}

void go_to_floor()
{
    // u8 i;
    CLR_BIT(P3, 0);
    // 1 5 5 5 5  CURRENT_FLOOR=3 NEXT_FLOOR=0
    if (CURRENT_FLOOR > requests[NEXT_FLOOR])
    {
        direction = -1;
        // for (i = 0; i < 5; i++)
        // {
        //     if (requests[i] == 5)
        //     {
        //         NEXT_FLOOR = i - 1;
        //         break;
        //     }
        // }
    }
    else
    {
        direction = 1;
        NEXT_FLOOR = 0;
    }

    while (CURRENT_FLOOR != requests[NEXT_FLOOR])
    {
        if (direction == -1)
            CURRENT_FLOOR--;
        else if (direction == 1)
            CURRENT_FLOOR++;
        // P0 = direction + 1;
        elevate(direction);
        seven_segment(CURRENT_FLOOR);
    }
    pop(requests, NEXT_FLOOR);
    SET_BIT(P3, 0);
    Delay_MS(1000);
}

int main()
{
    u8 floor;

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

        if (requests[0] == 5)
        {
            if (q_size != 0)
            {
                floor = dequeue();
                P0 = floor;
                push_value(requests, &requests_index, floor);
                go_to_floor();
            }
        }
        else
        {
            // 2 3 5 5 5
            // 3
            go_to_floor();
        }
    }
    return 0;
}

void request(void) interrupt 0
{
    u8 floor;
    if (!GET_BIT(P2, 2))
    {
        floor = GROUND_FLOOR;
        // floor 0
        if (CURRENT_FLOOR != floor)
        {
            if (requests[0] == 5)
            {
                push_value(requests, &requests_index, floor);
            }

            else if (direction == 1)
            {
                if (CURRENT_FLOOR < floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR > floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }

            else if (direction == -1)
            {
                if (CURRENT_FLOOR > floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR < floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }
        }
    }
    else if (!GET_BIT(P2, 3))
    {
        floor = 1;
        // floor 1
        if (CURRENT_FLOOR != floor)
        {

            if (requests[0] == 5)
            {
                direction = 1;
                push_value(requests, &requests_index, floor);
            }
            // 5 5 5 5 5 current 4
            // 2 5 5 5 5 current 4
            // 2 3 5 5 5 current 4
            else if (direction == 1)
            {
                if (CURRENT_FLOOR < floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR > floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }

            else if (direction == -1)
            {
                if (CURRENT_FLOOR > floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR < floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }
        }
    }

    else if (!GET_BIT(P2, 4))
    {
        floor = 2;
        // floor 2
        if (CURRENT_FLOOR != floor)
        {
            if (requests[0] == 5)
            {
                direction = 1;
                push_value(requests, &requests_index, floor);
            }

            else if (direction == 1)
            {
                if (CURRENT_FLOOR < floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR > floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }

            else if (direction == -1)
            {
                if (CURRENT_FLOOR > floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR < floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }
        }
    }
    else if (!GET_BIT(P2, 5))
    {
        floor = 3;
        // floor 3
        if (CURRENT_FLOOR != floor)
        {
            if (requests[0] == 5)
            {
                direction = 1;
                push_value(requests, &requests_index, floor);
            }

            else if (direction == 1)
            {
                if (CURRENT_FLOOR < floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR > floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }

            else if (direction == -1)
            {
                if (CURRENT_FLOOR > floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR < floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }
        }
    }
    else if (!GET_BIT(P2, 6))
    {
        floor = TOP_FLOOR;
        // floor 4
        if (CURRENT_FLOOR != floor)
        {
            if (requests[0] == 5)
            {
                direction = 1;
                push_value(requests, &requests_index, floor);
            }

            else if (direction == 1)
            {
                if (CURRENT_FLOOR < floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR > floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }

            else if (direction == -1)
            {

                if (CURRENT_FLOOR > floor)
                {
                    push_value(requests, &requests_index, floor);
                }
                else if (CURRENT_FLOOR < floor)
                {
                    push_value(pending_requests, &pending_requests_index, floor);
                }
            }
        }
    }
}

void request2(void) interrupt 2
{
    if (!GET_BIT(P2, 1))
    {
        if (CURRENT_FLOOR != GROUND_FLOOR)
            enqueue(GROUND_FLOOR);
    }
    if (!GET_BIT(P2, 0))
    {
        if (CURRENT_FLOOR != TOP_FLOOR)
            enqueue(TOP_FLOOR);
    }
}
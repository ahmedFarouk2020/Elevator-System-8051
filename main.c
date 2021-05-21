#include "C8051F020.h"
// #include "Headers/stack.h"
#include "Headers/BIT_MATH.h"
#include "Headers/STD_TYPES.h"
u8 requests[10] = {0};
u8 queue[5] = {0};
u8 index = 0;   // the place in array where the new value will be placed
u8 q_index = 0; // the place in array where the new value will be placed
u8 q_size = 0;
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
    if(q_size == 0)     q_index = 0;
    if(q_index <5){
        queue[q_index] = value;
        q_index++;
        q_size++;
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
int main()
{
    // Stack *ptr = &requests;
    // ptr->top = 0;
    
    // push(2, ptr);
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
    EA = 1;  // Enabling the global interrupt flag

    P2MDOUT = 0xff;
    P1 = 0x00; //LEDs
    
    // 01111111
    P2 = 0x7f; //CONTROL_PORTS
    
    index = 0;
    while (1)
    {

    }
    return 0;
}
void request(void) interrupt 0
{
    if(!GET_BIT(P2,0))
    {
        // going down request
        enqueue(1);
    }
    if(!GET_BIT(P2,1))
    {
        // going up request
        enqueue(2);
    }
    if(!GET_BIT(P2,2))
    {
        // push_value(2);
        // P0 = requests[0];
        TOG_BIT(P1, 1);
        // SET_BIT(P1,2);
    }
    if(!GET_BIT(P2,3))
    {
        // push_value(3);
        // P0 = requests[0];
        TOG_BIT(P1, 1);
        // SET_BIT(P1,3);
    }
    if(!GET_BIT(P2,4))
    {
        // push_value(0);
        // P0 = requests[0];
        TOG_BIT(P1, 1);
        // SET_BIT(P1,4);
    }
    if(!GET_BIT(P2,5))
    {
        // push_value(0);
        // P0 = requests[0];
        TOG_BIT(P1, 1);
        // SET_BIT(P1,5);
    }
    if(!GET_BIT(P2,6))
    {
        // push_value(0);
        // P0 = requests[0];
        TOG_BIT(P1, 1);
        // SET_BIT(P1,6);
    }
    
    
}
#include "C8051F020.h"
#include "Headers/BIT_MATH.h"
#include "Headers/STD_TYPES.h"

u8 requests[10] = {0};
u8 index = 0;   // the place in array where the new value will be placed
u8 queue[5] = {0};
u8 q_index = 0; // the place in array where the new value will be placed
u8 q_size = 0;
void add()
{
}

int main()
{
    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock

    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x00;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled
    
    IT0 = 1; // Configure interrupt 0 for falling edge on INT0
    EX0 = 1; // Enabling the EX0 interrupt
    EA = 1;  // Enabling the global interrupt flag

    P2MDOUT = 0xff;
    P1 = 0x00; //LEDs
    
    P2 = 0x03; //CONTROL_PORTS
    
    while (1)
    {

    }
    return 0;
}
void request(void) interrupt 0
{
    if(GET_BIT(P2,1))
    {
        TOG_BIT(P1,0);
    }
    if(GET_BIT(P2,0))
    {
        TOG_BIT(P1,1);
    }

}
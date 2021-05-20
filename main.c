#include "C8051F020.h"
// #include "Headers/stack.h"
#include "Headers/BIT_MATH.h"
#include "Headers/STD_TYPES.h"
// #include "set.h"

// STACK -------------------------------------------
/* MAX NUM OF ELEMENT IN STACK IS 100 */
#define MAXSTACK 10

/* REMEBER TO CHANGE THE FN diplay ACCORDING TO THIS */
#define StackEntry u8

typedef struct
{
    u8 top; /* POINTS TO THE LOCATION IN WHICH WE PUT THE DATA (ACCESS THEN INCREAMENT) */
    StackEntry entry[MAXSTACK];

}Stack;
void createStack(Stack* ptr_s)
{
    ptr_s->top = 0;
}

u8 push(StackEntry value , Stack* ptr_s)
{
    if(ptr_s->top == MAXSTACK)
        return 0;
    else    
    {
        ptr_s->entry[ptr_s->top++] = value ;
        return 1;
    }    
}


u8 StackFull(Stack* ptr_s)
{
    return((ptr_s->top == MAXSTACK));
}

u8 StackEmpty(Stack* ptr_s)
{
    return((ptr_s->top == 0));
}

void pop(StackEntry* pe , Stack* ptr_s)
{
    *pe = ptr_s->entry[-- ptr_s->top];
}

void clearStack(Stack* ptr_s)
{
    ptr_s->top = 0;
}
//  -------------------------------------------

// SET -----------------------------------------------------
u8 requests[10] = {0};
u8 index; // the place in array where the new value will be placed
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
// -----------------------------------------------------
void Delay_MS(u16 ms){
    u16 i;
    u16 j;
    for(i=0; i<ms; i++){
        for(j=0; j<120; j++){
        }
    }
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
    XBR1 = 0x00;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled
    
    IT0 = 1; // Configure interrupt 0 for falling edge on INT0
    EX0 = 1; // Enabling the EX0 interrupt
    EA = 1;  // Enabling the global interrupt flag

    P2MDOUT = 0xff;
    P1 = 0x00; //LEDs
    
    P2 = 0x03; //CONTROL_PORTS
    // Stack requests;
    
    // createStack(&requests);
    

    // REQUESTS_PORT = 0x00; //Control
    index = 0;
    Delay_MS(10);
    while (1)
    {

    }
    return 0;
}
void request(void) interrupt 0
{
    push_value(1);
    if(GET_BIT(P2,1))
    {
        TOG_BIT(P1,0); //toggle led_2
        // push 1 (up) to Stack
        // push(1, &requests);
    }
    if(GET_BIT(P2,0))
    {
        TOG_BIT(P1,1); //toggle led_2
        // push 0 (down) to Stack
        // push(0, &requests);
    }

}
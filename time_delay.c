#include <stdio.h>
#include <time.h>
void delay(int delay_in_milli_seconds){
    unsigned int delay_in_seconds = (delay_in_milli_seconds/1000) ;
    unsigned int finish_Time = time(0) + (delay_in_seconds);
    while(time(0)<finish_Time);
}

int main()
{
    int i;
    for (i = 0; i < 1; i++) {
        // delay of one second
        delay(20000);
        printf("%d seconds have passed\n", i + 1);
    }
    return 0;
}

// assume step angle = 45 so it needs 4 steps to complete 1 cycle
// assume the number of steps = 16 step to mave one completed floor  
//assume rotating clockwise will make the elevator go up and anti-clockwise will go down
void delay(){
    unsigned int i ;
    for(i = 0 ; i < 20000 ; i++) {
            continue ;
        }
}
const NUMBER_OF_STEPS = 16 ; // we can change to the desire number

void elevate(unsigned int current_floor,unsigned int destination) {
    // number of floors needed 
    signed int floors_number = destination - current_floor ;
    unsigned int i ;
    unsigned int value;
    if(P1 == 0x00) {
        return ;
    }
    if (floors_number > 0 ) {
        // we will go up
        // number of steps to reach the destination
        // 0001 -> 0010 -> 0100 -> 1000 -> 0001 -> ...
        unsigned int steps = NUMBER_OF_STEPS * (floors_number) ;
        P1 = 0x01;
        value = 0 ;
        for(i = 1 ; i <= steps ; i++) {
            value = P1 << 1 ;
            if(value == 0x10){
                P1 = 0x01 ;
            }else {
                P1 = value ;
            }
            delay();
        }
        P1 = 0x00;
    }
    else if (floors_number < 0 ) {
        // we will go down
        // number of steps to reach the destination
        // 1000 -> 0100 -> 0010 -> 0001 -> 1000 -> ...
        unsigned int steps = NUMBER_OF_STEPS * (floors_number * (-1) ) ;
        P1 = 0x08; // 00001000
        value = 0 ;
        for(i = 0 ; i < steps ; i++) {
            value = P1 >> 1 ;
            if(P1 == 0x00) {
                P1 = 0x08 ;
            }else {
                P1 = value ;
            }
            delay();
        }
        P1 = 0x00;
    }

}



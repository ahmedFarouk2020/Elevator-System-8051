#ifndef SET_H_
#define SET_H_

#define u8 int

u8 requests[10] = {0};
u8 index; // the place in array where the new value will be placed

/********************************/
/*          FUNCTIONS            */
/******************************/
u8 push_value(u8 value);
u8 Is_value_exist(u8 value);
void remove_index(u8 index);
void display(void);



#endif
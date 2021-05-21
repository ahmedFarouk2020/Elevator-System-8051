#ifndef SET_H_
#define SET_H_

#define u8 int

u8 requests[10] = {0};
u8 queue[5] = {0};
u8 index = 0;   // the place in array where the new value will be placed
u8 q_index = 0; // the place in array where the new value will be placed
u8 q_size = 0;
/********************************/
/*          FUNCTIONS            */
/******************************/
u8 push_value(u8 value);
u8 Is_value_exist(u8 value);
void remove_index(u8 index);
u8 enqueue(u8 value);
u8 dequeue(void);
void display(u8 arr[]);



#endif
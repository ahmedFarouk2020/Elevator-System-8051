/***********************************************************************************/
/* Author : FAROUK                                                                */
/* Date   : 21 SEP 2020                                                           */
/* Version: V01                                                                   */
/**********************************************************************************/
#ifndef STACK_H_
#define STACK_H_

#include "STD_TYPES.h"

/* MAX NUM OF ELEMENT IN STACK IS 100 */
#define MAXSTACK 10

/* REMEBER TO CHANGE THE FN diplay ACCORDING TO THIS */
#define StackEntry u8

typedef struct
{
    u8 top; /* POINTS TO THE LOCATION IN WHICH WE PUT THE DATA (ACCESS THEN INCREAMENT) */
    StackEntry entry[MAXSTACK];

}Stack;


void createStack(Stack* ptr_s);
u8 push(StackEntry value , Stack* ptr_s);
void pop(StackEntry* pe , Stack* ptr_s);
u8 StackFull(Stack* ptr_s);
u8 StackEmpty(Stack* ptr_s);
void clearStack(Stack* ptr_s);

#endif
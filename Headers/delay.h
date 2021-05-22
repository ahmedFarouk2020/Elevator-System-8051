#ifndef __DELAY_H__
#define __DELAY_H__
#include "STD_TYPES.h"

void Delay_MS(u16 ms)
{
    u16 i;
    u16 j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++)
        {
        }
    }
}

#endif
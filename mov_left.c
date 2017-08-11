#include <xc.h>
#include<pic.h>
#include <stdbool.h>
#include "config.h"
#include "bits_to_byte.h"
void mov_left (void)
{
    if(LEFT == 0 && RIGHT == 1)
    {
        __delay_ms(10);
    uchar temp_row_zero, temp_row_one,temp_row_two, row, col = 0;
    temp_row_zero = dropping[0][0]; // save data at [0][0]
    temp_row_one = dropping[1][0];  // save data at [1][0]
    temp_row_two = dropping[2][0];  // save data at [2][0]
    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 7; col++)
        {
            dropping[row][col] = dropping[row][col + 1];
        }
    }
    dropping[0][7] = temp_row_zero;
    dropping[1][7] = temp_row_one;
    dropping[2][7] = temp_row_two;
    bits_to_byte(&dropping[0][0], &dropping[8][0]);
    }
    //return col;
}

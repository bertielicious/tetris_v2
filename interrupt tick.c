#include <xc.h>
#include<pic.h>
#include <stdbool.h>
#include "config.h"
#include "drop_one_pixel.h"
#include "bits_to_byte.h"
#include "random.h"
#include "new_tetris_shape.h"
#include "clear_dropping.h"
#include "check_vert_collision.h"
#include "check_can_land.h"
#include "copy_dropping_to_stuck.h"
#include "check_bottom_boundary.h"
#include "interrupt tick.h"

void interrupt tick (void)
{
    extern bool collision;
    extern bool row16;
    extern uchar count;
    extern bool can_land;
   
    if (INTCONbits.TMR0IE = 1 && INTCONbits.T0IF == 1)       // TMR0 refreshes display of STUCK and DROPPING arrays
    {
        TMR0 = 0x00;                // 15Hz display refresh rate
        TMR0_LED = ~TMR0_LED;       // GREEN LED
        if(g == 0)
        {
            bits_to_byte(&dropping[0][0], &dropping[8][0]);     // display dropping[][] on LED matrices
            g = 1;   
        }
        else 
        {
            bits_to_byte(&stuck[0][0], &stuck[8][0]);           // display stuck[][] on LED matrices
            g = 0;   
        }
            INTCONbits.T0IF = 0;        // clear TMR0 interrupt flag
    }
    
    if (PIR1bits.TMR1IF == 1 )       // TMR1 is 0.5 sec gravity timer interrupt
    {
        TMR1H = 0x00;               // preload TMR1 to generate a 500ms interrupt
        TMR1L = 0x00;
        TMR1_LED = ~TMR1_LED;       // RED LED
        collision = check_vert_collision();
        row16 = check_bottom_boundary();
        if(row16 == 0 && collision == 0)
        { 
           drop_one_pixel();  
        }
        else
        {
            copy_dropping_to_stuck();
            clear_dropping();
            tet_piece = random();   // get a random num between 1 and 7
            new_tetris_shape(tet_piece); // copy tetrino into dropping[][]
            can_land = check_can_land();    // test to see there is space for new tetrino to land
            if(can_land == 1)
                {
                    clear_dropping();
                }
        }
        PIR1bits.TMR1IF = 0;            // clear TMR1IF to enable further interrupts
    }
    
}
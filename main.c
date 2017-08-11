#include <stdbool.h>
#include "config.h"
#include "init_ports.h"
#include "init_spi.h"
#include "init1_max7219.h"
#include "init2_max7219.h"
#include "splash_screen.h"
#include "clear_game_play_area.h"
#include "check_can_land.h"
#include "random.h"
#include "new_tetris_shape.h"
#include "copy_tetris.h"
#include "check_left_boundary.h"
#include "check_right_boundary.h"
#include "mov_left.h"
#include "mov_right.h"
#include "bits_to_byte.h"
#include "init_TMR0.h"
#include "rotate_tet.h"
#include "configTimer1.h"
#include "drop_one_pixel.h"
#include "clear_dropping.h"
#include "clear_stuck.h"

#include "main.h"

void main (void)
{
    uchar row, col, game_level = 0;
    bool moveR, moveL = 1;
    init_ports();
    init_spi();
    init1_max7219();
    init2_max7219();
    
    splash_screen();
    __delay_ms(2000);
    clear_game_play_area();
    clear_dropping();
    clear_stuck();
    tet_piece = random();   // get a random num between 1 and 7
    new_tetris_shape(tet_piece); // copy tetrino into dropping[][]
    can_land = check_can_land();    // test to see there is space for new tetrino to land
    if(can_land == 0)
    {
        bits_to_byte(&dropping[0][0], &dropping[8][0]);
        __delay_ms(100);
    init_TMR0();
    configTimer1();
    }
    

while(1)
    {
     moveL = check_left_boundary();  // 
     if( moveL == 0 && LEFT == 0)
        {
           mov_left();
        }
     
     moveR = check_right_boundary();
     if(moveR == 0 && RIGHT == 0)
        {
            mov_right();
        } 
     if (ROTATE == 0)
            {
            __delay_ms(50); 
          
            rotate_tet();
            }
    }      
 }
     

 
    


/*pseudocode for TETRIS  05/ 07/ 2017
 * initialise ports, SPI, Timer0 interrupt, Timer1 interrupt and displays
 * display tetris splash screen for 2 seconds
 * clear screen
 * game level = 0
 * enable TMR0 and TMR1 
 * call random() which randomly select one of seven tetris shapes to start the game
 *  get a random number between 1 and 7 and return rand_num to caller.
 *  select the tetris shape from  1 = sq, 2 = bar, 3 = z, 4 = s, 5 = l, 6 = j, 7 = t, then call copy_tetris function to copy tetris shape into dropping[][]
 *  call check_can_land - knowing where the piece will be initially placed at 
 *  pivot ([0][5]), check to see there are no existing obstacles preventing the tetris piece from landing.
 *  by comparing stuck[][]array with dropping[][]array
 *  if result == 1 
 *   the shape cannot be landed return bool 1 via obstacles variable
 * else
 *  the shape can be landed, return bool 0 via obstacles variable
 * if obstacles = 0
 *  land tetris shape at top of display
 * else
 *  game over
 *  clear game play area, display score achieved, wait for reset
 * 
 * do forever
 call check_left_boundary
 * for all rows and column zero of dropping[row][0] check 
 *  if ANDing with game_boarder[row+1][0] yields a 1
 *      return 1 via variable moveL     // cannot move further left
 *  else
 *      return 0 vial moveL             // can move further left
 * 
 *  if there is player input from Right button
 *      if there are no obstacles immediately 1 pixel right and we are not at RHS game border
 *          move tetris piece one pixel right
 *      else
 *          do not allow tetris piece to move right
 *  endif
 *  
 * 
 *  while there is player input from Left button
 *      if there are no obstacles immediately 1 pixel left and we are not at LHS game border
 *          move tetris piece one pixel left
 *      else
 *          do not allow tetris piece to move left
 * endif
 *    if there is player input from drop button
 *      if all pixels below tetris shape are empty
 *      drop shape to bottom row (row 16)
 *      copy to game_board array
 *      launch new tetris piece
 * 
 *      else
 *          do not allow tetris piece to drop
 *    if there are any fully completed rows
 *      clear the row and drop all tetris pieces above this line by one row
 *      award 1 point to the player
 *    if score is equal or  greater than that required to move to next level
 *      increment level
 *      increase game speed
 *      else
 *      do nothing
 *    if 0.5sec interrupt has occurred and
 *      if pixels one row below tetris shape are empty and we are not at row 16 (bottom)
 *      drop tetris shape by one pixel
 *      copy to game_board array
 *      else
 *          stick tetris shape forever
 *          launch new tetris piece
 * else
 *      stop 0.5 second timer interrupt
 *      call game_over function
 *      clear screen
 *      display score achieved
 * 
 * endif
 */
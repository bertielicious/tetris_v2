#include <xc.h>
#include<pic.h>
#include <stdbool.h>
#include "config.h"

bool check_bottom_boundary(void)
{
   uchar col;
   for(col = 0; col < 8; col++)
   {
       if(dropping[15][col] && game_boarder[17][col + 1] == 1)
       {
           return 1;    // tetrino is at bottom boundary
           break;
       }
   }
   return 0;            // tetrino is not at bottom boundary
}

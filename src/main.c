#include <gb/gb.h>
#include <stdio.h>
#include "mario.c"

UINT8 run_index = 0;

void main()
{
    SPRITES_8x16;
    set_sprite_data(0, 20, mario);
    set_sprite_tile(0, 0);
    move_sprite(0, 20, 20);
    set_sprite_tile(1, 2);
    move_sprite(1,20+8, 20);
    SHOW_SPRITES;
    while (1)
    {
        if(joypad()==J_RIGHT)
        {
            set_sprite_tile(0, (run_index+4)*2);
            set_sprite_tile(1, (run_index+4)*2+2);

            scroll_sprite(0, 2, 0);
            scroll_sprite(1, 2, 0);
            if(run_index==4)
            {
                run_index = 0;
            }
            else
            {
                run_index+=2;
            }
            
        }
        else if(joypad()==J_LEFT)
        {
            set_sprite_tile(0, (run_index+4)*2);
            set_sprite_tile(1, (run_index+4)*2+2);

            scroll_sprite(0, -2, 0);
            scroll_sprite(1, -2, 0);

            if(run_index==4)
            {
                run_index = 0;
            }
            else
            {
                run_index+=2;
            }
        }
        else 
        {
            set_sprite_tile(0, 0);
            set_sprite_tile(1, 2);
        }
        delay(80);
    }
    
}

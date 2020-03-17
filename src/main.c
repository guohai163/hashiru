#include <gb/gb.h>
#include <stdio.h>

unsigned char st[] =
{
  0x18,0x18,0x18,0x18,0x00,0x18,0x7E,0x7E,
  0x18,0x18,0x18,0x18,0x24,0x24,0x42,0x42
};

void main()
{
    set_sprite_data(0, 9, st);
    set_sprite_tile(0, 0);
    move_sprite(0, 20, 20);
    SHOW_SPRITES;
    while (1)
    {
        if(joypad()==J_RIGHT)
        {
            scroll_sprite(0, 2, 0);
        }
        if(joypad()==J_LEFT)
        {
            scroll_sprite(0, -2, 0);
        }
        delay(50);
    }
    
}

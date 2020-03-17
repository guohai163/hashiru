#include <gb/gb.h>
#include <stdio.h>
#include "game_role.h"
#include "mario.c"


UINT8 run_index = 0;

//定义角色
struct GameRole role;

/**
 * 初始化角色
 */
void initRole(UINT8 x, UINT8 y) 
{
    role.x = 0;
    role.y = 0;
    role.spritrun[0] = 8;
    role.spritrun[1] = 12;
    role.spritrun[2] = 16;
    role.spite_run_status = 0;
    set_sprite_tile(0, role.spritrun[role.spite_run_status]);
    role.spritids[0] = 0;
    set_sprite_tile(1, role.spritrun[role.spite_run_status]+2);
    role.spritids[1] = 1;
    role.direction = 2;
    movegamecharacter(&role,x,y);
    role.x = x;
    role.y = y;
}

void main()
{
    SPRITES_8x16;
    set_sprite_data(0, 20, mario);
    initRole(28,112);
    SHOW_SPRITES;
    while (1)
    {
        if(joypad()==J_RIGHT)
        {
            movegamecharacter(&role,role.x+2,role.y);
            role.x +=2;
            
        }
        else if(joypad()==J_LEFT)
        {
            movegamecharacter(&role,role.x-2,role.y);
            role.x -= 2 ;
        }
        else 
        {
            set_sprite_tile(0, 0);
            set_sprite_tile(1, 2);
        }
        delay(80);
    }
    
}

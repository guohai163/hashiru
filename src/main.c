#include <gb/gb.h>
#include <stdio.h>
#include "game_role.h"
#include "mario.h"

#include "background.h"
#include "mario-bg.h"


UINT8 run_index = 0;
BOOLEAN falsh_switch = FALSE;
UINT8 falsh_index = 1;
//定义角色
struct GameRole role;

//障碍
struct GameRole goomba;


const UWORD spritepalette[] = {

    marioCGBPal1c0,
    marioCGBPal1c1,
    marioCGBPal1c2,
    marioCGBPal1c3,

    marioCGBPal2c0,
    marioCGBPal2c1,
    marioCGBPal2c2,
    marioCGBPal2c3,

    marioCGBPal3c0,
    marioCGBPal3c1,
    marioCGBPal3c2,
    marioCGBPal3c3
};

const UWORD bkgpalette[] = {
    backgroundCGBPal0c0,
    backgroundCGBPal0c1,
    backgroundCGBPal0c2,
    backgroundCGBPal0c3,

    backgroundCGBPal1c0,
    backgroundCGBPal1c1,
    backgroundCGBPal1c2,
    backgroundCGBPal1c3,

    backgroundCGBPal2c0,
    backgroundCGBPal2c1,
    backgroundCGBPal2c2,
    backgroundCGBPal2c3,
};

/**
 * 初始化角色
 */
void initRole(UINT8 x, UINT8 y) 
{
    role.x = 0;
    role.y = 0;
    role.width = 10;
    role.height = 16;
    role.spritrun[0] = 8;
    role.spritrun[1] = 12;
    role.spritrun[2] = 16;
    role.spite_run_status = 0;
    set_sprite_tile(0, role.spritrun[role.spite_run_status]);
    role.spritids[0] = 0;
    set_sprite_prop(0,0);
    set_sprite_tile(1, role.spritrun[role.spite_run_status]+2);
    role.spritids[1] = 1;
    role.direction = 2;
    set_sprite_prop(1,0);
    movegamecharacter(&role,x,y);
    role.x = x;
    role.y = y;
}

/**
 * 初始化板栗仔
 */
void initGoomba(UINT8 x, UINT8 y)
{
    goomba.x = 0;
    goomba.y = 0;
    goomba.width = 10;
    goomba.height = 16;
    goomba.spritrun[0] = 20;
    goomba.spite_run_status = 0;
    goomba.spritids[0] = 2;
    goomba.spritids[1] = 3;
    set_sprite_tile(goomba.spritids[0], goomba.spritrun[goomba.spite_run_status]);
    set_sprite_tile(goomba.spritids[1], goomba.spritrun[goomba.spite_run_status]+2);
    movegameobstacle(&goomba,x,y);
    set_sprite_prop(2,2);
    set_sprite_prop(3,2);
    goomba.x = x;
    goomba.y = y;
    goomba.direction = 2;
}

/**
 * 休眠指定次数
 */
void performantdelay(UINT8 numloops)
{
    UINT8 i=0;
    for (   ; i < numloops; i++)
    {
        wait_vbl_done();
    }
    
}

void main()
{
    SPRITES_8x16;
    set_sprite_data(0, 24, mario);
    //引入调色板数据
    set_sprite_palette(0, 3, spritepalette);
    initRole(28,112);
    initGoomba(180, 112);
    SHOW_SPRITES;

    //设置背景数据源
    set_bkg_data(0,31,background);
    VBK_REG = 1;
    //加载背景数据
    set_bkg_tiles(0,0,marioBGWidth,marioBGHeight,marioBGPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0,0,marioBGWidth,marioBGHeight,marioBGPLN0);
    //加载背景配色方案
    set_bkg_palette(0, 3, bkgpalette);
    //调用显示背景方法
    SHOW_BKG;
    DISPLAY_ON;
    while (!checkcollisions(&role, &goomba))
    {
        movegameobstacle(&goomba, goomba.x-2, goomba.y);
        goomba.x -=2 ;
        if(joypad() & J_RIGHT)
        {
            // 当主角在屏幕中位置大于80时，不再移动主角只移动背景
            if(role.x >80){
                movegamecharacter(&role,role.x,role.y);
                scroll_bkg(4,0);
            }
            else
            {
                movegamecharacter(&role,role.x+4,role.y);
                role.x +=4;
            }
            
        }
        else if(joypad() & J_LEFT)
        {
            // 限制主角返回之前的位置，只有主角在屏幕位置小于16时才可以进行向左移动
            if(role.x>16){
                movegamecharacter(&role,role.x-4,role.y);
                role.x -= 4 ;
            }
        }
        else 
        {
            set_sprite_tile(0, 0);
            set_sprite_tile(1, 2);
        }
        if(joypad() == J_A)
        {
            falsh_switch = falsh_switch?FALSE:TRUE;
        }

        if(falsh_switch)
        {
            UINT8 prop = get_sprite_prop(0);
            prop = prop & 0xf8u;
            prop = prop | falsh_index;
            set_sprite_prop(0,prop );
            set_sprite_prop(1,prop );

            falsh_index = (falsh_index+1)%3;
        }
        else
        {
            UINT8 prop = get_sprite_prop(0);
            prop = prop & 0xf8u;
            set_sprite_prop(0,prop );
            set_sprite_prop(1,prop );
        }
        
        performantdelay(5);
    }
    printf("\n \n \n \n \n \n \n === GAME  OVER ===");
    
}

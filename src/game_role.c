#include "game_role.h"
/**
 * 移动精灵方法的实现
 */
void movegamecharacter(struct GameRole* character, UINT8 x, UINT8 y)
{
    //随着精灵的运动修改精灵的下标
    if(character->spite_run_status==2)
    {
        character->spite_run_status = 0;
    }
    else
    {
        character->spite_run_status++;
    }
    //运动状态时循环显示几个针的动画
    set_sprite_tile(character->spritids[0], character->spritrun[character->spite_run_status]);
    set_sprite_tile(character->spritids[1], character->spritrun[character->spite_run_status]+2);

    if(x<character->x && character->direction==2) {
        //向左移动
        set_sprite_prop(character->spritids[0], get_sprite_prop(character->spritids[0]) | S_FLIPX);
        set_sprite_prop(character->spritids[1], get_sprite_prop(character->spritids[1]) | S_FLIPX);
        character->direction = 4;
    }

    if(x>character->x && character->direction == 4) {
        //向右移动
        set_sprite_prop(character->spritids[0],get_sprite_prop(character->spritids[0]) & 0xdfu);
        set_sprite_prop(character->spritids[1],get_sprite_prop(character->spritids[1]) & 0xdfu);
        character->direction = 2;
    }
    //根据移动方向，移动精灵位置
    if(character->x!=x || character->y!=y) {
        if(character->direction ==2){
            move_sprite(character->spritids[0], x-4, y);
            move_sprite(character->spritids[1], x + sprite_size-4, y);
        }
        else if (character->direction == 4)
        {
            move_sprite(character->spritids[0], x, y);
            move_sprite(character->spritids[1], x - sprite_size, y);
        }
    }
}

/**
 * 障碍物的移动
 */
void movegameobstacle(struct GameRole* character, UINT8 x, UINT8 y)
{
    // 反复交替板栗仔的左右朝向，让板栗仔有一种左右踏脚的感觉
    if(character->direction == 2)
    {
        set_sprite_prop(character->spritids[0], get_sprite_prop(character->spritids[0]) | S_FLIPX);
        set_sprite_prop(character->spritids[1], get_sprite_prop(character->spritids[1]) | S_FLIPX);
        character->direction = 4;
    }
    else
    {
        set_sprite_prop(character->spritids[0],get_sprite_prop(character->spritids[0]) & 0xdfu);
        set_sprite_prop(character->spritids[1],get_sprite_prop(character->spritids[1]) & 0xdfu);
        character->direction = 2;
    }
    // 镜像后需要交替左右两个半截的位置
    if(character->direction ==2){
        move_sprite(character->spritids[0], x , y);
        move_sprite(character->spritids[1], x + sprite_size, y);
    }
    else if (character->direction == 4)
    {
        move_sprite(character->spritids[0], x+sprite_size, y);
        move_sprite(character->spritids[1], x , y);
    }

}

/**
 * 碰撞检查函数
 */
UBYTE checkcollisions(struct GameRole* one, struct GameRole* two)
{
    return (one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height);
}

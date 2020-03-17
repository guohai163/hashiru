#include <gb/gb.h>
#include <stdio.h>
/**
 * 游戏内角色的结构体,因为GB的机能限制，最大只支持8x16像素的sprit，
 * 因为我们每个角色使用32x32才能表示，所以一个数组来存储精灵的索引
 */
struct GameRole
{
    //精灵两个下标的存放数组
    UBYTE spritids[2];
    //精灵运动起来时的动画针索引
    UINT8 spritrun[3];
    //精灵的运动状态
    UINT8 spite_run_status;
    //精灵的x坐标
    UINT8 x;
    //精灵的y坐标
	UINT8 y;
    //精灵的面部朝向
    //1上，2右，3下，4左。我们这次只用左右和即可
    UINT8 direction;
};

//单个精灵瓦块的宽度
UINT8 sprite_size = 8;

/**
 * 移动精灵方法，我们要在.c文件中实现的
 */
void movegamecharacter(struct GameRole* character, UINT8 x, UINT8 y);

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
extern s32 player_bgx;
extern s32 player_bgy;
#include "../common.h"
class APlayer{
    public:
    s32 x,y,sx,sy;
    float g;
    u8 id,speedcap,cbg,screenc;
    u8 trampoline,utrampoline,death,co,bp;
    bool hflip;
    int checkCollisionRight(s32 x, s32 y, s8 speed);
    int checkCollisionLeft(s32 x, s32 y, s8 speed);
    int checkCollisionBottom(s32 x, s32 y);
    int Create(u8 id, s32 x, s32 y,u8 c,u8 b,u8 t, u8 d, u8 ut);
    int Move();
    int Gravity();
    int Update();
    int UpdateBg();
};

#endif
#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class ACrystal{
    public:
    s32 x,y,sx,sy;
    u8 alive,id,cbg;
    int Create(u8 id, u8 pal, s32 x, s32 y);
    int ReActivate();
    int vbl(s32 PlayerX,s32 PlayerY);
};
class ACannon{
    public:
    s32 x,y,sx,sy;
    bool alive,hflip;
    u8 id,sc,cb;
    int Create(u8 id, u8 pal, s32 x,s32 y, u8 sc, u8 cb);
    int ReActivate();
    int vbl(s32 PlayerX,s32 PlayerY);
};
class ASpring{
    public:
    int collision(s32 x,s32 y, s32 pointx, s32 pointy, s8 xp);
};
#endif
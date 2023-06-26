#include <PA9.h>
#include "objects.h"
#include "all_gfx.h"
#include "../common.h"

int ACrystal::Create(u8 id, u8 pal, s32 x, s32 y){
    this->x = x;
    this->y = y;
    this->id = id;
    this->cbg = cbg;
    PA_CreateSprite(1,id,(void*)crystal_Sprite,OBJ_SIZE_16X16,0,pal,x,y);
    PA_StartSpriteAnim(1,this->id,0,3,4);
    this->alive = true;
    return 0;
}
int ACrystal::ReActivate(){
    this->alive = true;
    return 0;
}
int ACrystal::vbl(s32 PlayerX, s32 PlayerY){
   this->sx = this->x - PA_BgInfo[1][2].ScrollX;
   this->sy = this->y - PA_BgInfo[1][2].ScrollY;
   if((this->sx < -16 || this->sx > 272 )||
   (this->sy < -16 || this->sy > 208)||
   this->alive == false) {
    this->sx = 256;
   }
   PA_SetSpriteXY(1,this->id,this->sx,this->sy);
   if((this->x < PlayerX+22 && this->x > PlayerX-8 )&&
   (this->y < PlayerY + 31 && this->y > PlayerY - 16)&&
   this->alive == true) {
        this->alive = false;
        this->sx = 256;
        mmEffect(SFX_CRYS);
        return 1;
   }
    return 0;
}
int ASpring::collision(s32 x,s32 y, s32 pointx, s32 pointy, s8 xp){
    if(x> pointx - 16 && x < pointx + xp &&
    y < pointy + 16 && y > pointy - 3)return 1;
    return 0;
}

int ACannon::Create(u8 id, u8 pal, s32 x,s32 y, u8 sc, u8 cb){
    this->id = id;
    this->x = x;
    this->y = y;
    this->sc = sc;
    this->cb = cb;
    this->alive = true;
    PA_CreateSprite(1,id,(void*)cannon_Sprite,OBJ_SIZE_16X16,0,pal,x,y);
    return 0;
}
int ACannon::ReActivate(){
    this->alive = true;
    return 0;
}
int ACannon::vbl(s32 PlayerX,s32 PlayerY){
    if(this->hflip == true) this->x ++;
    else this->x --;
    PA_SetSpriteHflip(1,this->id,this->hflip);
   this->sx = this->x - PA_BgInfo[1][2].ScrollX;
   this->sy = this->y - PA_BgInfo[1][2].ScrollY;
    if(PA_EasyBgGetPixel(0,2,this->sx + 16, this->sy) != 0) this->hflip = false;
    else if(PA_EasyBgGetPixel(0,2,this->sx - 16, this->sy) !=0) this->hflip = true;
    
    if(PA_EasyBgGetPixel(0,2,this->sx, this->sy + 16) == 0){
        if(this->hflip == true) this->hflip = false;
        else this->hflip = true;
    }
   if((this->sx < -16 || this->sx > 272 )||
   (this->sy < -16 || this->sy > 208)) {
   PA_SetSpriteX(1,this->id,256);
   }
   else if((this->x < PlayerX+8 && this->x > PlayerX-8 )&&
   (this->y < PlayerY + 16 && this->y > PlayerY - 16)) {
        return 1;
   }
   else PA_SetSpriteXY(1,this->id,this->sx,this->sy);
   return 0;
}
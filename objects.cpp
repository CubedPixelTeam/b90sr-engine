#include <PA9.h>
#include "objects.h"
#include "all_gfx.h"

int ACrystal::Create(int id, int pal, int x, int y){
    this->x = x;
    this->y = y;
    this->pal = pal;
    this->id = id;
    PA_CreateSprite(1,id,(void*)crystal_Sprite,OBJ_SIZE_16X16,0,pal,x,y);
    return 0;
}
int ACrystal::vbl(int PlayerX, int PlayerY){
    this->sx = (this->x - PA_BgInfo[1][2].ScrollX) - 4;
    this->sy = (this->y - PA_BgInfo[1][2].ScrollY) - 4;

    if ((this->sx < -(16-1)) || (this->sx >= 256) ||
    (this->sy < -(16-1)) || (this->sy >= 256)) {
        PA_SetSpriteX(1,this->id, 256);
    }
    else {
        PA_SetSpriteXY(1,this->id,this->sx,this->sy);
    }
    return 0;
}
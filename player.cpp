#include <PA9.h>
#include "player.h"
#include "all_gfx.h"
int rightDistance = 0;
int APlayer::checkCollisionRight(int x, int y, int speed){
	for(int i = 1; i < 30; i ++) if(PA_EasyBgGetPixel(1,this->cbg,x + 22 + speed, y + i) != 0) return 1;
	return 0;
}
int APlayer::checkCollisionLeft(int x, int y, int speed){
	for(int i = 1; i < 30; i ++) if(PA_EasyBgGetPixel(1,this->cbg,x + 5 + speed,y+i) != 0) return 1;
	return 0;
}
int APlayer::checkCollisionBottom(int x, int y){
	for(int i = 9; i < 22; i ++) if(PA_EasyBgGetPixel(1,this->cbg,x+i,y) != 0) return 1;
	return 0;
}
int APlayer::Create(int id, int x, int y){
    this->id = id;
	this->x = x;
	this->y = y;
	PA_LoadSpritePal(1,id,(void*)dar_Pal);
	PA_CreateSprite(1,id,(void*)dar_Sprite,OBJ_SIZE_16X32,1,id,x,y);
	PA_SetSpriteDblsize(1,id,1);
	PA_SetSpriteRotEnable(1,id,0);
	PA_SetRotsetNoAngle(1,0,194,192);
    return 0;
}
int distance = 0;
int APlayer::Move(){
	if(Pad.Held.Right && (checkCollisionRight(this->sx,this->sy + 1,this->speedcap) == 0)) {
		if(this->vx < this->speedcap) this->vx += 0.5;
		else if(this->vx > this->speedcap) this->vx = this->speedcap;
		this->x += this->vx;
		this->hflip = false;
	}
	else if(Pad.Held.Left && (checkCollisionLeft(this->sx - this->speedcap,this->sy + 1,this->speedcap) == 0)) {
		if(this->vx < this->speedcap) this->vx += 0.5;
		else if(this->vx > this->speedcap) this->vx = this->speedcap;
		this->x -= this->vx;
		this->hflip = true;
	}
	if(Pad.Newpress.Left){
		this->hflip = true;
		PA_StartSpriteAnim(1,this->id,7,10,15);
	}
	else if(Pad.Newpress.Right){
		this->hflip = false;
		PA_StartSpriteAnim(1,this->id,1,4,15);
	}
	if(Pad.Held.Y || Pad.Held.X){
		this->speedcap = 5;
	}
	else if(!(Pad.Held.Y || Pad.Held.X)) this->speedcap = 2;
	if(!(Pad.Held.Right || Pad.Held.Left)) {
		PA_SpriteAnimPause(1,this->id,1);
		if(this->hflip == false) PA_SetSpriteAnimFrame(1,this->id,0);
		else PA_StartSpriteAnim(1,this->id,7,10,5);
		this->vx = 0;
	}
	return 0;
}
bool touchingGround = false;
int jumptimer = 0;
bool jump = false;
int APlayer::Gravity(){
	if(checkCollisionBottom(this->sx,this->sy + 32 + this->g) == 0){
		PA_SpriteAnimPause(1,this->id,1);
		this->g += 0.4;
		if(this->hflip == false) PA_SetSpriteAnimFrame(1,this->id,5);
		else PA_SetSpriteAnimFrame(1,this->id,11);
	}
	else{
		for(int i = 0; i < this->g; i ++){
			if(checkCollisionBottom(this->sx,this->sy + 32 + distance) == 0) distance ++;
		}
		this->y += distance;
		distance = 0;
		this->g = 0;
		if(PA_GetSpriteAnimFrame(1,this->id) == 5) PA_StartSpriteAnim(1,this->id,1,4,15);
		else if(PA_GetSpriteAnimFrame(1,this->id) == 11) PA_StartSpriteAnim(1,this->id,7,10,15);
		if(Pad.Newpress.A) {
			touchingGround = true;
			jumptimer = 0;
			this->g = -7;
		}
	}
	if(checkCollisionBottom(this->sx,this->sy + this->g) != 0){
		for(int i = 0; i < this->g; i ++){
			if(checkCollisionBottom(this->sx,this->sy + 32 + distance) == 0) distance ++;
		}
		this->y += distance;
		distance = 0;
		this->g = 0;
    }
	this->y += this->g;
	if(Pad.Held.A && touchingGround == true){
		jumptimer ++;
		if(jumptimer < 12){
		this->g = -5;
		}
		else touchingGround = false;
	}
	else touchingGround = false;
    return 0;
}
int bg_x = 0;
int bg_y = 0;
int APlayer::UpdateBg(){
	PA_ClearTextBg(0);
	rightDistance += Pad.Newpress.Down - Pad.Newpress.Up;
	PA_OutputText(0,0,0,"%d",rightDistance);
    bg_x = this->x - 128;
    if(bg_x < 0) bg_x = 0;
    bg_y = this->y - 96;
    if(bg_y < 0) bg_y = 0;

    this->sx = (this->x - bg_x) - 4;
    this->sy = (this->y - bg_y) - 4;
    return 0;
}
int APlayer::Update(){
    PA_SetSpriteXY(1,this->id,this->sx,this->sy - 22);
    PA_EasyBgScrollXY(1,this->cbg,bg_x,bg_y);
    return 0;
}
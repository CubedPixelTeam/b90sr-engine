#include <PA9.h>
#include "player.h"
#include "all_gfx.h"
bool touchingGround = true;
int jumptimer = 0;
bool jump = false;
int APlayer::checkCollisionRight(s32 x, s32 y, s8 speed){
	for(int i = -1; i < 31; i ++) {
		u8 pixel = PA_EasyBgGetPixel(this->screenc,this->cbg,x + 22 + speed, y + i);
		if(pixel != 0) return pixel;
	}
	return 0;
}
int APlayer::checkCollisionLeft(s32 x, s32 y, s8 speed){
	for(int i = -1; i < 31; i ++) {
		u8 pixel = PA_EasyBgGetPixel(this->screenc,this->cbg,x + (8 - speed),y+i);
		if(pixel != 0) return pixel;
	}
	return 0;
}
int APlayer::checkCollisionBottom(s32 x, s32 y){
	for(int i = 10; i < 21-this->speedcap; i ++) {
		u8 pixel = PA_EasyBgGetPixel(this->screenc,this->cbg,x+i,y);
		if(pixel != 0) return pixel;
		//else if(PA_EasyBgGetPixel(this->screenc,this->cbg,x+i,y) == 2) return 2;
	}
	return 0;
}
int APlayer::Create(u8 id, s32 x, s32 y,u8 c,u8 b,u8 t, u8 d, u8 ut){
    this->id = id;
	this->x = x;
	this->y = y;
	this->hflip = false;
	this->speedcap = 2;
	this->trampoline = t;
	this->death = d;
	this->utrampoline = ut;
	this->co = c;
	this->bp = b;

	PA_LoadSpritePal(1,id,(void*)dar_Pal);
	PA_CreateSprite(1,id,(void*)dar_Sprite,OBJ_SIZE_16X32,1,id,x,y);
	PA_SetSpriteDblsize(1,id,1);
	PA_SetSpriteRotEnable(1,id,0);
	PA_SetRotsetNoAngle(1,0,194,192);
    return 0;
}
int distance = 0;
int APlayer::Move(){
	u8 pixel = checkCollisionRight(this->sx,this->sy + 1,this->speedcap);
	if(Pad.Held.Right && ((pixel == 0) || (pixel == this->bp))) {
		this->x += this->speedcap;
		this->hflip = false;
	}	
	else if(Pad.Held.Right && (pixel == this->death))return 1;
	pixel = checkCollisionLeft(this->sx,this->sy + 1,this->speedcap);
	if(Pad.Held.Left && ((pixel == 0) || (pixel == bp))) {
		this->x -= this->speedcap;
		this->hflip = true;
	}
	else if(Pad.Held.Left && (pixel == this->death)) return 1;
	
	if(Pad.Newpress.Left){
		this->hflip = true;
		PA_StartSpriteAnim(1,this->id,7,10,15);
	}
	else if(Pad.Newpress.Right){
		this->hflip = false;
		PA_StartSpriteAnim(1,this->id,1,4,15);
	}
	if(Pad.Held.Y || Pad.Held.X){
		this->speedcap = 4;
	}
	else if(!(Pad.Held.Y || Pad.Held.X)||
	(Pad.Held.Right && (checkCollisionRight(this->sx,this->sy + 1,this->speedcap+1) != 0))||
	(Pad.Held.Left && (checkCollisionLeft(this->sx,this->sy + 1,this->speedcap+1) != 0))) this->speedcap = 2;
	if(!(Pad.Held.Right || Pad.Held.Left)) {
		PA_SpriteAnimPause(1,this->id,1);
		if(this->hflip == false) PA_SetSpriteAnimFrame(1,this->id,0);
		else PA_StartSpriteAnim(1,this->id,6,10,5);
	}
	return 0;
}
int delay_timer = 0;
int APlayer::Gravity(){
	s8 pixel = checkCollisionBottom(this->sx,this->sy + 32 + this->g);
	if(pixel == 0){
		PA_SpriteAnimPause(1,this->id,1);
		this->g += 0.4;
		delay_timer ++;
		if(delay_timer > 40) delay_timer = 40;
		else if(delay_timer < 9 && this->g > 0){
			if(Pad.Newpress.A || Pad.Newpress.B) {
				touchingGround = true;
				jumptimer = 10;
				this->g = -1;
				mmEffect(SFX_JUMP);
			}
		}
		if(this->hflip == false) PA_SetSpriteAnimFrame(1,this->id,5);
		else PA_SetSpriteAnimFrame(1,this->id,11);
	}
	else if(pixel == this->co||
	(pixel == this->bp && this->g >= 0)){
		for(int i = 0; i < this->g; i ++){
			if(checkCollisionBottom(this->sx,this->sy + 32 + distance) == 0) distance ++;
		}
		this->y += distance;
		distance = 0;
		this->g = 0;
		delay_timer = 0;
		if(PA_GetSpriteAnimFrame(1,this->id) == 5) PA_StartSpriteAnim(1,this->id,1,4,15);
		else if(PA_GetSpriteAnimFrame(1,this->id) == 11) PA_StartSpriteAnim(1,this->id,6,10,15);
		if(Pad.Newpress.A || Pad.Newpress.B) {
			touchingGround = true;
			jumptimer = 0;
			this->g = -7;
			mmEffect(SFX_JUMP);
		}
	}
	if(pixel == this->trampoline) this->g = -13; 
	else if(pixel == this->death) return 1; 
	else if(pixel == this->utrampoline) this->g = -19; 
	
/*	if(pixel == 3) this->g = -13;
	else if(pixel == 4) return 1;
	else if(pixel == 5) this->g = -19;
*/
	pixel = checkCollisionBottom(this->sx,this->sy + this->g);
	if(pixel == this->death) return 1; 
	if(pixel == this->co ||
	(pixel == this->bp && this->g >= 0)){
		for(int i = 0; i < this->g; i ++){
			if(checkCollisionBottom(this->sx,this->sy + 32 + distance) == 0) distance ++;
		}
		this->y += distance;
		distance = 0;
		this->g = 0;
		touchingGround = false;
    }
	this->y += this->g;
	if((Pad.Held.A || Pad.Held.B) && touchingGround == true){
		jumptimer ++;
		if(jumptimer < 12){
		this->g = -4;
		}
		else touchingGround = false;
	}
	else touchingGround = false;
	if(this->g > 7) this->g = 10;
    return 0;
}
s32 player_bgx = 0;
s32 player_bgy = 0;
int APlayer::UpdateBg(){
    player_bgx = this->x - 128;
    player_bgy = this->y - 96;
    return 0;
}
int APlayer::Update(){
    this->sx = (this->x - player_bgx) - 4;
    this->sy = (this->y - player_bgy) - 4;
    PA_SetSpriteXY(1,this->id,this->sx,this->sy - 22);
    PA_EasyBgScrollXY(1,this->cbg,player_bgx,player_bgy);
    return 0;
}

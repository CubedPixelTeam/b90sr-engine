#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class APlayer{
    public:
    float x;
    float y;
    float g;
    float vx;
    float vy;
    float sx;
    float sy;
    int id;
    bool hflip;
    int speedcap;
    int cbg;
    int checkCollisionRight(int x, int y, int speed);
    int checkCollisionLeft(int x, int y, int speed);
    int checkCollisionBottom(int x, int y);
    int Create(int id, int x, int y);
    int Move();
    int Gravity();
    int Update();
    int UpdateBg();
};

#endif
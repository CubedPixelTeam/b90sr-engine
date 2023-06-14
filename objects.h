#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class ACrystal{
    public:
    float x;
    float y;
    int id;
    int pal;
    int sx;
    int sy;
    int Create(int id, int pal, int x, int y);
    int vbl(int PlayerX,int PlayerY);
};
class ASpring{
    public:
    int collision(int x,int y, int pointx, int pointy);
};
#endif
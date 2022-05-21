#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "common.h"

class BulletObject : public BaseObject
{

public:
    BulletObject();
    ~BulletObject();

    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
    };
    enum BulletType
    {
        BASE_BULLET = 50,
        LASER_BULLET = 51,
        THREAT_BULLET = 52,
    };

    void set_x_val(const int& xVal) {x_val = xVal;}

    int get_x_val() const {return x_val;}

    void set_is_move(const bool& isMove) {is_move = isMove;}
    bool get_is_move() const {return is_move;}

    void HandleMove(const int& x_border, const int& y_border);

    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir = bulletDir;}
    unsigned int get_bullet_dir() const {return bullet_dir;}

    void set_bullet_type(const unsigned int& bulletType) {bullet_type = bulletType;}
    unsigned int get_bullet_type() const {return bullet_type;}

    bool LoadImgBullet(SDL_Renderer* des);

private:
    int x_val;
    int y_val;
    bool is_move;
    unsigned int bullet_dir;
    unsigned int bullet_type;
};


#endif // BULLET_OBJECT_H_

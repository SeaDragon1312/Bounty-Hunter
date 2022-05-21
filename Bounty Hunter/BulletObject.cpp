#include "stdafx.h"
#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val = 0;
    y_val = 0;
    is_move = false;
    bullet_type = BASE_BULLET;
}

BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if(bullet_type == LASER_BULLET)
    {
        ret = LoadImg("img//laser_bullet.png", des);
    }
    else if(bullet_type == BASE_BULLET){
        ret = LoadImg("img//player_bullet.png", des);
    }
    else if(bullet_type == THREAT_BULLET){
        ret = LoadImg("img//player_bullet1.png", des);
    }
    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if(bullet_dir == DIR_RIGHT){
        rect.x += x_val;
        if(rect.x > x_border)
        {
            is_move = false;
        }
    }
    else if(bullet_dir == DIR_LEFT){
        rect.x -= x_val;
        if(rect.x < 0){
            is_move = false;
        }
    }
}

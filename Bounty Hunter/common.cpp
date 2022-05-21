#include "common.h"
#include "stdafx.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;                         // tọa độ đường đứng bên trái vật 1
    int right_a = object1.x + object1.w;            // tọa độ đường đứng bên phải vật 1
    int top_a = object1.y;                          // tọa độ đường ngang phía trên vật 1
    int bottom_a = object1.y + object1.h;           // tọa độ đường ngang phía dưới vật 1

    int left_b = object2.x;                         // tọa độ đường đứng bên trái vật 2
    int right_b = object2.x + object2.w;            // tọa độ đường đứng bên phải vật 2
    int top_b = object2.y;                          // tọa độ đường ngang phía trên vật 2
    int bottom_b = object2.y + object2.h;           // tọa độ đường ngang phía dưới vật 2

    // Case 1: kích thước object1 nhỏ hơn kích thước object2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: kích thước object2 lớn hơn object1
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

       // Case 3: kích thước 2 vật bằng nhau
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

bool SDLCommonFunc::CheckCollisionMouse(int x, int y,const SDL_Rect& obj)
{
    int left_a = obj.x;                         // tọa độ đường đứng bên trái vật 1
    int right_a = obj.x + obj.w;            // tọa độ đường đứng bên phải vật 1
    int top_a = obj.y;                          // tọa độ đường ngang phía trên vật 1
    int bottom_a = obj.y + obj.h;           // tọa độ đường ngang phía dưới vật 1

    if(x>=left_a && x<=right_a && y<=bottom_a && y>= top_a){
        return true;
    }
    else{
        return false;
    }
}

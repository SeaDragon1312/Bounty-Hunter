#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    width_frame = 0;
    height_frame = 0;
    x_pos = 0.0;
    y_pos = 0.0;
    x_val = 0.0;
    y_val = 0.0;
    on_ground = false;
    come_back_time = 0;
    frame = 0;

    animation_a = 0;
    animation_b = 0;
    input_type.left = 0;
    type_move = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret)
    {
        width_frame = rect.w/THREAT_FRAME_NUM;
        height_frame = rect.h;
    }
    return ret;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect1;
    rect1.x = rect.x;
    rect1.y = rect.y;
    rect1.w = width_frame;
    rect1.h = height_frame;

    return rect1;
}

void ThreatsObject::set_clips()
{
    if(width_frame>0&&height_frame>0)
    {
        for(int i=0; i<THREAT_FRAME_NUM; i++){
            frame_clips[i].x=i*width_frame;
            frame_clips[i].y=0;
            frame_clips[i].w=width_frame;
            frame_clips[i].h=height_frame;
        }
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if(come_back_time == 0)
    {
        rect.x = x_pos - map_x_;
        rect.y = y_pos - map_y_;
        frame++;
        if(frame >= 8){
            frame = 0;
        }
        SDL_Rect* currentClip = &frame_clips[frame];
        SDL_Rect rendQuad = {rect.x, rect.y, width_frame, height_frame};
        SDL_RenderCopy(des, p_object, currentClip, &rendQuad);
    }
}

void ThreatsObject::DoPlayer(Map& map_data)
{
    if(come_back_time == 0)
    {
        x_val = 0;
        y_val += THREAT_GRAVITY_SPEED;
        if(y_val >= THREAT_MAX_FALL_SPEED)
        {
            y_val = THREAT_MAX_FALL_SPEED;
        }

        if(input_type.left == 1)
        {
            x_val -= THREAT_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += THREAT_SPEED;
        }

        CheckToMap(map_data);
    }
    else if(come_back_time >0)
    {
        come_back_time --;
        if(come_back_time == 0)
        {
            InitThreats();
        }
    }
}

void ThreatsObject::InitThreats()
{
    x_val = 0;
    y_val = 0;
    if(x_pos > 256)
    {
        x_pos -= 256;
        animation_a -= 256;
        animation_b -= 256;
    }
    else{
        x_pos = 0;
    }
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    input_type.left = 1;
}

void ThreatsObject::RemoveBullet(const int& idx)
{
    int size = bullet_list.size();
    if(size > 0 && idx < size)
    {
        BulletObject* p_bullet = bullet_list[idx];
        bullet_list.erase(bullet_list.begin()+idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void ThreatsObject::CheckToMap(Map& map_data)           // copy lại từ main và sửa đổi đôi chút
{
    int x1 = 0;                                         // các biến x1,x2,y1,y2 xác định ô nv đang ở trong bản đồ
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //check chiều ngang
    int height_min = min(height_frame, TILE_SIZE);

    x1 = (x_pos + x_val)/TILE_SIZE;                     // tính x1 đang ở ô nào của bản đồ
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;   // trừ 1 để có một sai số nhỏ không để x2 trùng TILE_SIZE

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val>0) // nhân vật di chuyển sang bên phải thì check với x2
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if((val1 != BLANK_TILE && val1 != MONEY) || (val2 != BLANK_TILE && val2 != MONEY))
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if(x_val < 0)         //nhân vật di chuyển sang bên trái
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if((val1 != BLANK_TILE && val1 != MONEY) || (val2 != BLANK_TILE && val2 != MONEY))
            {
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }

    //check chiều dọc
    int width_min = min(width_frame, TILE_SIZE);
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if(y_val>0)     //nhân vật đang rơi xuống
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if((val1 != BLANK_TILE && val1 != MONEY) || (val2 != BLANK_TILE && val2 != MONEY))
            {
                y_pos = y2*TILE_SIZE;
                y_pos -=  (height_frame +1);
                y_val = 0;

                on_ground = true;
            }
        }
        else if(y_val<0)        //nhân vật đang nhảy lên
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if((val1 != BLANK_TILE && val1 != MONEY) || (val2 != BLANK_TILE && val2 != MONEY)){
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }

    x_pos += x_val;     // cho nhân vật di chuyển
    y_pos += y_val;

    if(x_pos < 0){
        x_pos = 0;
    }
    else if(x_pos + width_frame > map_data.max_x){
        x_pos = map_data.max_x - width_frame - 1;
    }

    if(y_pos > map_data.max_y)
    {
        come_back_time = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move == STATIC_THREAT)
    {
        ;//
    }
    else{
        if(on_ground == true)
        {
            if(x_pos > animation_b)
            {
                input_type.left = 1;
                input_type.right = 0;
                LoadImg("img//threat_left.png", screen);
            }
            else if(x_pos < animation_a)
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("img//threat_right.png", screen);
            }
        }
        else
        {
            if(input_type.left == 1)
            {
                LoadImg("img//threat_left.png", screen);
            }
        }
    }
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::THREAT_BULLET);
        bool ret = p_bullet->LoadImgBullet(screen);

        if(ret)
        {
            p_bullet->set_is_move(true);

            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->setRect(rect.x + 10, rect.y + 10);
            p_bullet->set_x_val(15);
            bullet_list.push_back(p_bullet);

        }
    }
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_linit, const int& y_linit)
{
    for(int i = 0; i < bullet_list.size(); i++)
    {
        BulletObject* p_bullet = bullet_list[i];
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move())
            {
                int bullet_distance = rect.x + width_frame - p_bullet->GetRect().x;

                if(bullet_distance < 300 && bullet_distance > 0)
                {
                    p_bullet->HandleMove(x_linit, y_linit);
                    p_bullet->Render(screen);
                }
                else{
                    p_bullet->set_is_move(false);
                }
            }

            else
            {
                p_bullet->set_is_move(true);
                p_bullet->setRect(rect.x + 10, rect.y + 10);
            }
        }
    }
}

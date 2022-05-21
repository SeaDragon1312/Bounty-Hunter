#include "stdafx.h"
#include "MainObject.h"

MainObject::MainObject()    //hàm khởi tạo
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = WALK_NONE;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.down = 0;
    input_type.up = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    come_back_time = 0;
    money_count = 0;    //khởi tạo số đồng xu ăn được bằng 0
}

MainObject::~MainObject()   //hàm hủy
{
    Free();
}

bool MainObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true){
        width_frame = rect.w/8;     // chiều dài lấy 1/8 chiều dài ảnh
        height_frame = rect.h;
    }
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect1;
    rect1.x = rect.x;
    rect1.y = rect.y;
    rect1.w = width_frame;
    rect1.h = height_frame;

    return rect1;
}

void MainObject::set_clips()
{
    if(width_frame>0&&height_frame>0)
    {
        for(int i=0; i<=7; i++){
            frame_clip[i].x=i*width_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void MainObject::Show(SDL_Renderer* des)        // thay đổi hoạt ảnh nv
{
    UpdateImagePlayer(des);

    if(input_type.left==1 || input_type.right==1){
        frame++;
    }
    else{
        frame = 0;
    }

    if(frame>=8){
        frame=0;
    }

    if(come_back_time == 0)
    {
        rect.x = x_pos - map_x_;            // do màn hình cuốn theo nhân vật nên phải trừ đi 1 lượng map_x_ (ở đây là vị trí bắt đầy map.start_x)
        rect.y = y_pos - map_y_;

        SDL_Rect* current_clip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
        SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
    }
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN){
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status = WALK_RIGHT;
                input_type.right = 1;
                input_type.left = 0;
                UpdateImagePlayer(screen);
            }
            break;
        case SDLK_a:
            {
                status = WALK_LEFT;
                input_type.left = 1;
                input_type.right = 0;
                UpdateImagePlayer(screen);
            }
            break;
        case SDLK_w:
            {
                input_type.jump = 1;
                UpdateImagePlayer(screen);
            }
        }
    }
    else if(events.type == SDL_KEYUP){
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                input_type.right = 0;
            }
            break;
        case SDLK_a:
            {
                input_type.left = 0;
            }
            break;
        }
    }

    if(events.type == SDL_MOUSEBUTTONDOWN)                  // click chuột để bắn đạn
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            BulletObject* p_bullet = new BulletObject();
            p_bullet->set_bullet_type(BulletObject::BASE_BULLET);
            p_bullet->LoadImgBullet(screen);

            // âm thanh đạn chuột trái
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
			{
				cout << Mix_GetError() << endl;
			}
            Mix_Chunk* gBullet = Mix_LoadWAV("audio//fire.wav");
            Mix_PlayChannel(-1, gBullet, 0);

            if(status == WALK_LEFT){
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                p_bullet->setRect(this->rect.x, rect.y + height_frame*0.25);
            }
            else{
                p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                p_bullet->setRect(this->rect.x + width_frame - 20, rect.y + height_frame*0.25);
            }

            p_bullet->set_x_val(20);
            p_bullet->set_is_move(true);

            p_bullet_list.push_back(p_bullet);
        }
        else if(events.button.button == SDL_BUTTON_RIGHT)
        {
            BulletObject* p_bullet = new BulletObject();
            p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
            p_bullet->LoadImgBullet(screen);

            // thêm âm thanh chuột phải
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
			{
				cout << Mix_GetError() << endl;
			}
            Mix_Chunk* gBullet = Mix_LoadWAV("audio//laser.wav");
            Mix_PlayChannel(-1, gBullet, 0);

            if(status == WALK_LEFT){
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                p_bullet->setRect(this->rect.x, rect.y + height_frame*0.25);
            }
            else{
                p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                p_bullet->setRect(this->rect.x + width_frame - 20, rect.y + height_frame*0.25);
            }

            p_bullet->set_x_val(20);
            p_bullet->set_is_move(true);

            p_bullet_list.push_back(p_bullet);
        }
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)                    //hàm nạp đạn để bắn
{
    for(int i= 0; i<p_bullet_list.size(); i++){
        BulletObject* p_bullet = p_bullet_list[i];
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else{
                p_bullet_list.erase(p_bullet_list.begin()+i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int& idx)           // hàm xóa đạn
{
    int size = p_bullet_list.size();
    if(size > 0 && idx < size)
    {
        BulletObject* p_bullet = p_bullet_list[idx];
        p_bullet_list.erase(p_bullet_list.begin()+idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void MainObject::DoPlayer(Map& map_data)
{
    if(come_back_time == 0)
    {
        x_val = 0;
        y_val += GRAVITY_SPEED;

        if(y_val >= MAX_FALL_SPEED){
            y_val = MAX_FALL_SPEED;
        }

        if(input_type.left == 1){
            x_val -= PLAYER_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += PLAYER_SPEED;
        }

        if(input_type.jump == 1){
            if(on_ground == true){
                //âm thanh nhảy
                Mix_Chunk* jumb = Mix_LoadWAV("audio//jumb.wav");
                Mix_PlayChannel(-1, jumb, 0);
                y_val = -PLAYER_JUMP_VAL;
            }
            on_ground = false;
            input_type.jump = 0;
        }
        CheckToMap(map_data);
        CenterEntityOnMap(map_data);
    }

    if(come_back_time > 0)
    {
        come_back_time--;
        if(come_back_time == 0){

            on_ground = false;
            if(x_pos > 256){
                x_pos -= 256;  //4 tile map
            }
            else{
                x_pos = 0;
            }
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}

void MainObject::CenterEntityOnMap(Map& map_data)       // hàm kéo map theo nhân vật
{
    map_data.start_x = x_pos - (SCREEN_WIDTH/2);
    if(map_data.start_x < 0){
        map_data.start_x = 0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x){
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }
    map_data.start_y = y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y < 0){
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y){
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

void MainObject::CheckToMap(Map& map_data)
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

            if(val1 == MONEY|| val2 == MONEY) //nếu chạm đồng tiền
            {
                map_data.tile[y1][x2] = 0;    // không hiện lên nữa
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
            }
            else{                             //không chạm đồng tiền
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos = x2*TILE_SIZE;
                    x_pos -= width_frame + 1;
                    x_val = 0;
                }
            }
        }
        else if(x_val < 0)         //nhân vật di chuyển sang bên trái
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 == MONEY|| val2 == MONEY) //nếu chạm đồng tiền
            {
                map_data.tile[y1][x1] = 0;    // không hiện lên nữa
                map_data.tile[y2][x1] = 0;
                IncreaseMoney();
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos = (x1+1)*TILE_SIZE;
                    x_val = 0;
                }
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
            if(val1 == MONEY || val2 == MONEY)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos = y2*TILE_SIZE;
                    y_pos -=  (height_frame +1);
                    y_val = 0;

                    on_ground = true;
                    if(status == WALK_NONE){
                        status = WALK_RIGHT;
                    }
                }
            }
        }
        else if(y_val<0)        //nhân vật đang nhảy lên
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == MONEY || val2 == MONEY){
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseMoney();
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE){
                    y_pos = (y1 + 1)*TILE_SIZE;
                    y_val = 0;
                }
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

void MainObject::IncreaseMoney()
{
    money_count++;
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
    {
        cout << Mix_GetError() << endl;
    }

    Mix_Chunk *gBullet = Mix_LoadWAV( "audio//coin.wav" );
    Mix_PlayChannel( -1, gBullet, 0 );
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if(on_ground == true){
        if(status == WALK_LEFT){
            LoadImg("Img//player_left.png", des);
        }
        else{
            LoadImg("img//player_right.png", des);
        }
    }
    else{
        if(status == WALK_LEFT){
            LoadImg("img//jum_left.png", des);
        }
        else{
            LoadImg("img//jum_right.png", des);
        }
    }
}


//NHỚ SỬA LẠI TÊN CỬA SỐ GAME :D
// làm thêm chức năng tắt nhạc và sound effect

#include "stdafx.h"
#include "common.h"
#include "BaseObject.h"
#include "Game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "PlayerPower.h"
//#include "menu.h"

BaseObject g_background;
BaseObject menu_background;
BaseObject pause_background;
BaseObject tutorial_background;
BaseObject play_bottom;
BaseObject play_bottom_pressed;
BaseObject exit_button;
BaseObject exit_button_pressed;
BaseObject continue_button;
BaseObject continue_button_pressed;
BaseObject remuse_button;
BaseObject remuse_button_pressed;
BaseObject pause_icon;
BaseObject tutorial_icon;
BaseObject music_icon;
BaseObject music_off_icon;
BaseObject win_png;
BaseObject lose_png;
TTF_Font* font_time = NULL;
Uint32 time_in_menu;

bool is_quit = false;
int music_count_click = 0;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Du an game cuoi ky",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL){
        success = false;
    }
    else{
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL){
            success = false;
        }
        else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags))&&imgFlags){
                success = false;
            }
        }
        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("font//font.ttf", 30);
        if(font_time == NULL)
        {
            success = false;
        }
    }
    return success;
}

bool LoadBackGround()
{
    bool ret = g_background.LoadImg("img/background/background.png", g_screen);
    ret = menu_background.LoadImg("img/background/menu1_background.png", g_screen);
    ret = tutorial_background.LoadImg("img/background/tutorial.png", g_screen);
    ret = pause_icon.LoadImg("img/button/pause.png", g_screen);
    ret = tutorial_icon.LoadImg("img/button/howtoplay.png", g_screen);
    ret = music_icon.LoadImg("img/button/music.png", g_screen);
    ret = music_off_icon.LoadImg("img/button/music_off.png", g_screen);
    if(ret == false){
        return false;
    }
    return true;
}

void close()
{
    g_background.Free();
    menu_background.Free();
    play_bottom.Free();
    play_bottom_pressed.Free();
    exit_button.Free();
    exit_button_pressed.Free();
    remuse_button.Free();
    remuse_button_pressed.Free();
    pause_icon.Free();
    tutorial_background.Free();
    tutorial_icon.Free();
    music_icon.Free();
    music_off_icon.Free();
    win_png.Free();
    lose_png.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

vector <ThreatsObject*> MakeThreatList()
{
    vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for(int i = 0; i < 20; i++)                                     // đối tượng threat động
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 +i*500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[20];

    for(int i = 0; i < 20; i++)                                         // đối tượng threat tĩnh
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_level.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(700+i*1200);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int menu()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout << Mix_GetError() << endl;
	}
    Mix_Music* rose = NULL;
	rose = Mix_LoadMUS("audio/baicuavo.mp3");
	Mix_PlayMusic(rose, -1);

	Mix_Chunk* click = Mix_LoadWAV("audio/click.wav");

    if(LoadBackGround()==false){
        return -1;
    }

    bool ret = play_bottom.LoadImg("img/button/play.png", g_screen);
    play_bottom.setRect(SCREEN_WIDTH*0.5+210, SCREEN_HEIGHT*0.1);

    ret = play_bottom_pressed.LoadImg("img/button/play_pressed.png", g_screen);
    play_bottom_pressed.setRect(SCREEN_WIDTH*0.5+210, SCREEN_HEIGHT*0.1);

    ret = exit_button.LoadImg("img/button/exit.png", g_screen);
    exit_button.setRect(SCREEN_WIDTH*0.5+210, SCREEN_HEIGHT*0.3);

    ret = exit_button_pressed.LoadImg("img/button/exit_pressed.png", g_screen);
    exit_button_pressed.setRect(SCREEN_WIDTH*0.5+210, SCREEN_HEIGHT*0.3);

    bool quit = false;
    while(!quit)
    {
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    is_quit=true;
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, play_bottom.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                    }
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                        is_quit = true;
                    }
                }
            }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        menu_background.Render(g_screen, NULL);

        play_bottom.Render(g_screen);
        exit_button.Render(g_screen);
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, play_bottom.GetRect())){
            play_bottom_pressed.Render(g_screen);
        }
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect())){
            exit_button_pressed.Render(g_screen);
        }

        SDL_RenderPresent(g_screen);
    }
    Mix_FreeMusic(rose);
    time_in_menu = SDL_GetTicks();              // lấy thời gian ở trong menu vì SDL_GetTick() bấm giờ khi chương trình bắt đầu chạy
    menu_background.Free();
    play_bottom.Free();
    play_bottom_pressed.Free();
    return 0;
}

int pause()
{
    Uint32 start_time_in_pause = SDL_GetTicks();                // thời điểm bắt đầu pause

	Mix_Chunk* click = Mix_LoadWAV("audio/click.wav");

    if(LoadBackGround()==false){
        return -1;
    }

    bool ret = remuse_button.LoadImg("img/button/resume.png", g_screen);
    remuse_button.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.5-150);

    ret = remuse_button_pressed.LoadImg("img/button/resume_pressed.png", g_screen);
    remuse_button_pressed.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.5-150);

    ret = exit_button.LoadImg("img/button/exit.png", g_screen);
    exit_button.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.5);

    ret = exit_button_pressed.LoadImg("img/button/exit_pressed.png", g_screen);
    exit_button_pressed.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.5);

    bool quit = false;
    while(!quit)
    {
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    is_quit=true;
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, remuse_button.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                    }
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                        is_quit = true;
                    }
                }
            }

        remuse_button.Render(g_screen);
        exit_button.Render(g_screen);
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, remuse_button.GetRect())){
            remuse_button_pressed.Render(g_screen);
        }
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect())){
            exit_button_pressed.Render(g_screen);
        }

        SDL_RenderPresent(g_screen);
    }
    Uint32 finish_time_in_pause = SDL_GetTicks();                   // kết thúc pause
    time_in_menu += (finish_time_in_pause - start_time_in_pause);    // cộng thời gian pause vào time_in_menu
    menu_background.Free();
    remuse_button.Free();
    remuse_button_pressed.Free();

    return 0;
}

int tutorial()
{
    Uint32 start_time_in_tutorial = SDL_GetTicks();                // thời điểm bắt đầu pause

	Mix_Chunk* click = Mix_LoadWAV("audio/click.wav");

    if(LoadBackGround()==false){
        return -1;
    }

    bool ret = continue_button.LoadImg("img/button/continue.png", g_screen);
    continue_button.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.5);

    ret = continue_button_pressed.LoadImg("img/button/continue_pressed.png", g_screen);
    continue_button_pressed.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.5);

    bool quit = false;
    while(!quit)
    {
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    is_quit=true;
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, continue_button.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                    }
                }
            }

        tutorial_background.Render(g_screen, NULL);

        continue_button.Render(g_screen);
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, continue_button.GetRect())){
            continue_button_pressed.Render(g_screen);
        }

        SDL_RenderPresent(g_screen);
    }
    Uint32 finish_time_in_tutorial = SDL_GetTicks();                   // kết thúc pause
    time_in_menu += (finish_time_in_tutorial - start_time_in_tutorial);    // cộng thời gian pause vào time_in_menu
    continue_button.Free();
    continue_button_pressed.Free();

    return 0;
}

int win()
{
    Uint32 start_time_in_pause = SDL_GetTicks();                // thời điểm bắt đầu pause

    Mix_Music* win = NULL;
	win = Mix_LoadMUS("audio/win.mp3");
	Mix_PlayMusic(win, -1);

	Mix_Chunk* click = Mix_LoadWAV("audio/click.wav");

    bool ret = win_png.LoadImg("img/background/win1.png", g_screen);
    win_png.setRect(SCREEN_WIDTH*0.5-170, SCREEN_HEIGHT*0.1);

    ret = exit_button.LoadImg("img/button/exit.png", g_screen);
    exit_button.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.6 - 20);

    ret = exit_button_pressed.LoadImg("img/button/exit_pressed.png", g_screen);
    exit_button_pressed.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.6 - 20);

    bool quit = false;
    while(!quit)
    {
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    is_quit=true;
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                        is_quit = true;
                    }
                }
            }

        win_png.Render(g_screen);
        exit_button.Render(g_screen);
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect())){
            exit_button_pressed.Render(g_screen);
        }

        SDL_RenderPresent(g_screen);
    }
    Uint32 finish_time_in_pause = SDL_GetTicks();                   // kết thúc pause
    time_in_menu += (finish_time_in_pause - start_time_in_pause);    // cộng thời gian pause vào time_in_menu
    Mix_FreeMusic(win);
    menu_background.Free();
    exit_button.Free();
    exit_button_pressed.Free();

    return 0;
}

int lose()
{
    Uint32 start_time_in_pause = SDL_GetTicks();                // thời điểm bắt đầu pause

    Mix_Chunk* gameover = Mix_LoadWAV("audio/gameover.wav");
    Mix_PlayChannel(-1, gameover, 0);

	Mix_Chunk* click = Mix_LoadWAV("audio/click.wav");

    bool ret = win_png.LoadImg("img/background/gameover.png", g_screen);
    win_png.setRect(SCREEN_WIDTH*0.5-175, SCREEN_HEIGHT*0.1+50);

    ret = exit_button.LoadImg("img/button/exit.png", g_screen);
    exit_button.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.6 - 20);

    ret = exit_button_pressed.LoadImg("img/button/exit_pressed.png", g_screen);
    exit_button_pressed.setRect(SCREEN_WIDTH*0.5-100, SCREEN_HEIGHT*0.6 - 20);

    bool quit = false;
    while(!quit)
    {
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    is_quit=true;
                }
                if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN){
                        Mix_PlayChannel(-1, click, 0);
                        quit = true;
                        is_quit = true;
                    }
                }
            }

        win_png.Render(g_screen);
        exit_button.Render(g_screen);
        if(SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect())){
            exit_button_pressed.Render(g_screen);
        }

        SDL_RenderPresent(g_screen);
    }
    Uint32 finish_time_in_pause = SDL_GetTicks();                   // kết thúc pause
    time_in_menu += (finish_time_in_pause - start_time_in_pause);    // cộng thời gian pause vào time_in_menu
    menu_background.Free();
    exit_button.Free();
    exit_button_pressed.Free();

    return 0;
}

void music()
{
    if(music_count_click % 2 == 1)
    {
        Mix_PauseMusic();
    }
    else{
        Mix_ResumeMusic();
    }
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    if(InitData()==false){
        return -1;
    }

    menu();
    if(LoadBackGround()==false){
        return -1;
    }

    // Load Music
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout << Mix_GetError() << endl;
	}
	Mix_Music* bgm = NULL;
	bgm = Mix_LoadMUS("audio/nhacgame.mp3");
	Mix_PlayMusic(bgm, -1);
	Mix_VolumeMusic(30);

    Mix_Chunk* click = Mix_LoadWAV("audio/click.wav"); // tiếng click chuột

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");          //load file map
    game_map.LoadTIles(g_screen);               //load tile từng ô map

    MainObject p_player;                        // nhân vật chính p_player
    p_player.LoadImg("img//player_right.png", g_screen);        // bắt đầu trò chơi với trạng thái nhân vật quay về bên phải
    p_player.set_clips();

    // số mạng
    PlayerPower player_power;
    player_power.Init(g_screen);

    // số tiền thu được
    PlayerMoney player_money;
    player_money.Init(g_screen);


    vector <ThreatsObject*> threats_list = MakeThreatList();

    // load ảnh vụ nổ quái
    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
    if(!tRet){
        return -1;
    }

    // ảnh nổ nhân vật
    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("img//exp3.png", g_screen);
    if (!mRet){
        return -1;
    }
    exp_threat.set_clips();
    exp_main.set_clips();

    int num_die = 0;

    //Time text
    TextObject time_game;
    time_game.SetColor(TextObject::BLACK_TEXT);
    // điểm
    TextObject mark_game;
    mark_game.SetColor(TextObject::BLACK_TEXT);
    UINT mark_value = 0;
    // money
    TextObject money_game;
    money_game.SetColor(TextObject::BLACK_TEXT);
    //rule
    TextObject rule;
    rule.SetColor(TextObject::BLACK_TEXT);

    while(!is_quit)                             // bắt đầu game loop
    {
        fps_timer.start();                      // bấm giờ
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit=true;
            }
            else if(SDLCommonFunc::CheckCollisionMouse(xm, ym, pause_icon.GetRect()))
            {
                if(g_event.type == SDL_MOUSEBUTTONDOWN){
                    Mix_PlayChannel(-1, click, 0);
                    Mix_PauseMusic();
                    pause();
                    break;
                }
            }
            else if(SDLCommonFunc::CheckCollisionMouse(xm, ym, tutorial_icon.GetRect()))
            {
                if(g_event.type == SDL_MOUSEBUTTONDOWN){
                    Mix_PlayChannel(-1, click, 0);
                    tutorial();
                    break;
                }
            }
            else if(SDLCommonFunc::CheckCollisionMouse(xm, ym, music_icon.GetRect()))
            {
                if(g_event.type == SDL_MOUSEBUTTONDOWN){
                    Mix_PlayChannel(-1, click, 0);
                    music_count_click++;
                    music();
                    break;
                }
            }
            p_player.HandleInputAction(g_event, g_screen);  //bắt thao tác bàn phím và chuột
        }

        //nếu đang tắt nhạc thì bật lại
        if(music_count_click % 2 == 0){
            Mix_ResumeMusic();
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        Map map_data = game_map.getMap();


        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x, map_data.start_y);

        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        player_power.Show(g_screen);
        player_money.Show(g_screen);
        player_money.SetPos(SCREEN_WIDTH*0.4 - 140, 8);

        // load icon
        pause_icon.setRect(580, 592);
        pause_icon.Render(g_screen);

        tutorial_icon.setRect(700, 590);
        tutorial_icon.Render(g_screen);

        music_icon.setRect(640, 590);
        music_off_icon.setRect(640, 590);

        if(music_count_click % 2 == 1)
        {
            music_off_icon.Render(g_screen);
        }
        else{
            music_icon.Render(g_screen);
        }

        for(int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list[i];
            if(p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x, map_data.start_y);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                //SDL_Rect rect_player = p_player.GetRectFrame();
                SDL_Rect rect_player;
                rect_player.x = p_player.GetRect().x+7;
                rect_player.y = p_player.GetRect().y;
                rect_player.w = p_player.get_width_frame();
                rect_player.h = p_player.get_height_frame();
                bool bCol1 = false;
                vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for(int jj = 0; jj < tBullet_list.size(); jj++)
                {
                    BulletObject* pt_bullet = tBullet_list[jj];
                    if(pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        /*if(bCol1)
                        {
                            p_threat->RemoveBullet(jj);
                            break;
                        }*/
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

                if(bCol1 || bCol2 || int(p_player.get_y()/64)==10)
                {
                    if(bCol1 || bCol2)
                    {
                        //nhân vật chết do bị bắn thì hét lên đau đớn
                        Mix_Chunk* pain = Mix_LoadWAV("audio//pain.wav");
                        Mix_PlayChannel(-1, pain, 0);

                        int width_exp_frame = exp_main.get_frame_height();
                        int heiht_exp_height = exp_main.get_frame_width();
                        for (int ex = 0; ex < 4; ex++)
                        {
                            int x_pos = (p_player.GetRect().x + p_player.get_width_frame()*0.5) - width_exp_frame*0.5;
                            int y_pos = (p_player.GetRect().y + p_player.get_height_frame()*0.5) - heiht_exp_height*0.5;

                            exp_main.set_frame(ex);
                            exp_main.setRect(x_pos, y_pos);
                            exp_main.Show(g_screen);
                            SDL_RenderPresent(g_screen);
                        }
                    }
                    else{           // chết do rơi xuống vực thì la hét sợ hãi
                        Mix_Chunk* pain = Mix_LoadWAV("audio//falling_scream.wav");
                        Mix_PlayChannel(-1, pain, 0);
                    }

                    num_die++;
                    if(num_die < 3){
                        p_player.setRect(0,0);
                        p_player.Setxypos(p_player.get_x(),0);
                        p_player.SetComebackTime(60);
                        SDL_Delay(1000);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        continue;
                    }
                    else
                    {
                        Mix_FreeMusic(bgm);
                        p_threat->Free();
                        lose();
                    }
                }
            }
        }

        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for(int r = 0; r < bullet_arr.size(); ++r)
        {
            BulletObject* p_bullet = bullet_arr[r];
            if(p_bullet != NULL)
            {
                for(int t = 0; t < threats_list.size(); ++t)
                {
                    ThreatsObject* obj_threat = threats_list[t];
                    if(obj_threat != NULL)
                    {
                        SDL_Rect tRect = obj_threat->GetRectFrame();
                        SDL_Rect bRect  = p_bullet->GetRect();
                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if(bCol)
                        {
                            mark_value++;

                            // âm thanh quái nổ
                            Mix_Chunk* boom = Mix_LoadWAV("audio//boom.wav");
                            Mix_VolumeChunk(boom, 30);
                            Mix_PlayChannel(-1, boom, 0);

                            for(int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;        // trừ frame_exp_width*0.5 để vụ nổ ở giữa viên đạn
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
                                exp_threat.set_frame(ex);
                                exp_threat.setRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }
                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }

        //Show game time
        string str_time = "Time: ";
        Uint32 time_val = (SDL_GetTicks() - time_in_menu) / 1000;
        Uint32 val_time = 100 - time_val;
        if(val_time <= 0)
        {
            Mix_FreeMusic(bgm);
            lose();
        }
        else{
            string str_val = to_string(val_time);
            str_time +=str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 180, 5);
        }
        //show mark
        string val_str_mark = to_string(mark_value);
        string strMark = "Enemies killed: ";
        strMark += val_str_mark;
        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5+50, 5);
        //show money
        int money_count = p_player.GetMoneyCount();
        string money_str = to_string(money_count);
        if(money_count == 30)
        {
            Mix_FreeMusic(bgm);
            win();
        }
        else{
            money_str+="/30";
            money_game.SetText(money_str);
            money_game.LoadFromRenderText(font_time, g_screen);
            money_game.RenderText(g_screen, SCREEN_WIDTH*0.4 - 100, 5);
        }
        //show rule
        string str = "You have 3 lives and 100s to try to collect 30 bitcoins!!";
        rule.SetText(str);
        rule.LoadFromRenderText(font_time, g_screen);
        rule.RenderText(g_screen, SCREEN_WIDTH - 900, 30);


        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;  //ms

        if(real_imp_time < time_one_frame){
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >=0){
                SDL_Delay(delay_time);
            }
        }
    }

    for(int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list[i];
        if(p_threat != NULL)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }

    threats_list.clear();

    close();
    return 0;
}


// Bạn có 100 giây và 3 mạng để cố gắng thu thập 30 đồng xu

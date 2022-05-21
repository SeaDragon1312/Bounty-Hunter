
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


/*#include "commonFunc.h"
#include "include.h"
#include "Texture.h"
#include "Timer.h"

bool click_button(Texture button);
//Menu
void init_menu();
void render_menu();
void show_menu();
void close_menu();
void show_options();

Texture play_button;
Texture option_button;
Texture sound_button;
Texture music_button;
Texture game_name;
Texture back_ground;

Mix_Chunk* click_sound;
Mix_Music* menu_sound;

void init_menu()
{
    back_ground.loadFromFile("img/menu1.png");
    back_ground.setRect(0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    game_name.loadFromFile("img/game_name.jpg");
    game_name.setRect(100,100);

    play_button.loadFromFile("img/button/play.png");
    play_button.setRect(520,390);
    option_button.loadFromFile("img/button/option.png");
    option_button.setRect(520,490);

    click_sound = Mix_LoadWAV("sound/click.wav");
    menu_sound = Mix_LoadMUS("sound/menu.mp3");
    if(!Mix_PlayingMusic()) Mix_PlayMusic(menu_sound, -1);

}
void render_menu()
{
    SDL_RenderClear(Game::renderer);

    back_ground.renderTexture(NULL);
    game_name.renderTexture(NULL);

    SDL_PollEvent(&Game::event);
    if(Game::event.type == SDL_QUIT) Game::status_ = QUIT;
    if(Game::event.type == SDL_MOUSEBUTTONDOWN){
        Mix_PlayChannel(-1,click_sound,0);
    }
    int xm,ym;
    SDL_GetMouseState(&xm,&ym);

    if(Collision::CheckFocus(xm,ym,play_button.getRect()) == true)
    {
        play_button.loadFromFile("img/button/play_pressed.png");
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            Game::status_ = START;
            Mix_FreeMusic(menu_sound);
            Mix_FreeChunk(click_sound);
        }
    }
    else play_button.loadFromFile("img/button/play.png");

    if(Collision::CheckFocus(xm,ym,option_button.getRect()) == true)
    {
        option_button.loadFromFile("img/button/option_pressed.png");
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            Game::status_ = OPTIONS;
        }
    }
    else option_button.loadFromFile("img/button/option.png");

    play_button.renderTexture(NULL);
    option_button.renderTexture(NULL);

    SDL_RenderPresent(Game::renderer);

    Game::fps.keep_fps();
}

void close_menu()
{
    //fps.stop();
    back_ground.Free();
    play_button.Free();
    option_button.Free();
    music_button.Free();
    sound_button.Free();
}

void show_menu()
{
    init_menu();
    while(Game::status_ == MENU){
         render_menu();
    }
    close_menu();
}

int choose_weapon(const int& x, const int& y )
{
    SDL_Rect rect_= {};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

        }
    }
    return 0;
}

void show_options()
{
    Texture table_player1;
    Texture table_player2;
    table_player1.loadFromFile("img/weapon/weapon_table.jpg");
    table_player1.setRect(150,200,264,264);
    table_player2.loadFromFile("img/weapon/weapon_table.jpg");
    table_player2.setRect(SCREEN_WIDTH-430,200,264,264);

    Texture menu_button;
    menu_button.setRect(SCREEN_WIDTH/2-130,400,180,60);

    back_ground.loadFromFile("img/options.png");
    back_ground.setRect(0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    while(Game::status_ == OPTIONS){
        SDL_RenderClear(Game::renderer);
        //check mouse
        SDL_PollEvent(&Game::event);
        if(Game::event.type == SDL_QUIT) Game::status_ = QUIT;
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            Mix_PlayChannel(-1,click_sound,0);
        }
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);

        if(Collision::CheckFocus(xm,ym,menu_button.getRect()) == true)
        {
            menu_button.loadFromFile("img/button/menu_pressed.png");
            if(Game::event.type == SDL_MOUSEBUTTONDOWN){
                    Game::status_ = MENU;
                    Mix_PlayChannel(-1,click_sound,0);
            }
        }
        else menu_button.loadFromFile("img/button/menu.png");




        //render
        back_ground.renderTexture(NULL);
        menu_button.renderTexture(NULL);
        table_player1.renderTexture(NULL);
        table_player2.renderTexture(NULL);
        SDL_RenderPresent(Game::renderer);

        Game::fps.keep_fps();
    }

    table_player1.Free();
    table_player2.Free();
    back_ground.Free();
}

*/

#endif // MENU_H_INCLUDED

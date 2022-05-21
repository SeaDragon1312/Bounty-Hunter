#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//screen
const int FRAME_PER_SECOND = 25;  // fps
const int SCREEN_WIDTH = 1280;    // chiều rộng màn hình
const int SCREEN_HEIGHT = 640;    // chiều cao màn hình
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;


#define TILE_SIZE 64        // 1 ô tile map
#define MAX_MAP_X 400       // chiều rộng tối đa

#define MAX_MAP_Y 10        // chiều cao tối đa
#define BLANK_TILE 0        // vùng không có map

#define MONEY 4             // vùng có đồng xu

typedef struct Input        // lớp thao tác
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};

typedef struct Map          //  lớp map
{
    int start_x;            // vị trí bắt đầu vẽ map
    int start_y;

    int max_x;              //chiều dài của map
    int max_y;              //chiều cao của map

    int tile[MAX_MAP_Y][MAX_MAP_X];     // mảng map
    char* filename;                     // file map
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);      // hàm kiểm tra va chạm đạn với threat
    bool CheckCollisionMouse(int x, int y, const SDL_Rect& obj);                // kiểm tra vị trí của chuột có trong hình ảnh không
}

#endif  // COMMON_FUNCTION_H_

#include "BaseObject.h"
#include "stdafx.h"

BaseObject::BaseObject()    // hàm khởi tạo
{
    p_object = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BaseObject::~BaseObject()   // hàm hủy
{
    Free();
}

bool BaseObject::LoadImg(string path, SDL_Renderer* screen)                             // hàm load ảnh
{
    Free();                                                                             // giải phóng trước
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));   // xóa font màu rgb
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);                // gán surface cho texture
        if(new_texture != NULL){
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_object = new_texture;
    return p_object != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip  /* =NULL */)
{
    SDL_Rect renderquad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(des, p_object, clip, &renderquad);

}

void BaseObject::Free()     // hàm giải phóng
{
    if(p_object != NULL){
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}

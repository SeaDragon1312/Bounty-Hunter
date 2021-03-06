#include "stdafx.h"
#include "Explosion.h"

ExplosionObject::ExplosionObject()
{
    frame_height = 0;
    frame_width = 0;
    frame = 0;
}

ExplosionObject::~ExplosionObject()
{
    Free();
}

bool ExplosionObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if(ret)
    {
        frame_width = rect.w/ NUM_FRAME_EXP;
        frame_height = rect.h;
    }

    return ret;
}

void ExplosionObject::set_clips()
{
    if(frame_width>0&&frame_height>0)
    {
        for(int i=0; i<NUM_FRAME_EXP; i++){
            frame_clip[i].x=i*frame_width;
            frame_clip[i].y=0;
            frame_clip[i].w=frame_width;
            frame_clip[i].h=frame_height;
        }
    }
}

void ExplosionObject::Show(SDL_Renderer* screen)
{
    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect render_quad = {rect.x, rect.y, frame_width, frame_height};
    if(current_clip != NULL)
    {
        render_quad.w = current_clip->w;
        render_quad.h = current_clip->h;
    }

    SDL_RenderCopy(screen, p_object, current_clip, &render_quad);
}

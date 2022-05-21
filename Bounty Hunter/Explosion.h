#ifndef EXP_H_
#define EXP_H_

#include "common.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 8

class ExplosionObject : public BaseObject
{

public:
    ExplosionObject();
    ~ExplosionObject();

public:
    void set_clips();
    void set_frame(const int& fr) {frame = fr;}
    virtual bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return frame_width;}
    int get_frame_height() const {return frame_height;}

private:
    int frame_width;
    int frame_height;

    unsigned int frame;
    SDL_Rect frame_clip[8];
};




#endif // EXP_H_

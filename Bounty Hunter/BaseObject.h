
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "common.h"

class BaseObject
{
public:
    BaseObject();       //hàm khởi tạo
    ~BaseObject();      //hàm hủy
    void setRect(const int& x, const int& y){
        rect.x = x; rect.y = y;
    }
    SDL_Rect GetRect() const
    {
        return rect;
    }
    SDL_Texture* GetObject() const
    {
        return p_object;
    }

    virtual bool LoadImg(string path, SDL_Renderer* screen);        // hàm load ảnh
    void Render(SDL_Renderer* des , const SDL_Rect* clip = NULL);   // show ảnh lên màn hình
    void Free();                                                    // hàm giải phóng

protected:
    SDL_Texture* p_object;
    SDL_Rect rect;
};

#endif // BASE_OBJECT_H_

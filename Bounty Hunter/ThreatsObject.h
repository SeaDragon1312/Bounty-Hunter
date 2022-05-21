#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "common.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_FRAME_NUM 8
#define THREAT_SPEED 3

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();            // hàm khởi tạo
    ~ThreatsObject();           // hàm hủy

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_val(const float& xVal) {x_val = xVal;}
    void set_y_val(const float& yVal) {y_val = yVal;}

    void set_x_pos(const float& xPos) {x_pos = xPos;}
    void set_y_pos(const float& yPos) {y_pos = yPos;}

    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}

    void SetMapXY(const int&mapx, const int& mapy)  {map_x_ = mapx; map_y_ = mapy;}

    void set_clips();
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void InitThreats();

    void set_type_move(const int& typeMove) {type_move = typeMove;}
    int GetTypeMove() const {return type_move;}

    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a = pos_a; animation_b = pos_b;}
    void set_input_left(const int& ipLeft) {input_type.left = ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);
    SDL_Rect GetRectFrame();

    vector <BulletObject*> get_bullet_list() const {return bullet_list;}
    void set_bullet_list(const vector<BulletObject*>& bl_list) {bullet_list = bl_list;}

    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_linit, const int& y_linit);      // cho threat tĩnh bắn đạn
    void RemoveBullet(const int& idx);


private:                        // các biến tương tự MainObject

    int map_x_;
    int map_y_;

    float x_pos;
    float y_pos;

    float x_val;
    float y_val;

    bool on_ground;
    int come_back_time;                         // comeback time tương tự Main
    SDL_Rect frame_clips[THREAT_FRAME_NUM];     // các hoạt ảnh quái
    int width_frame;            // chiều dài và chiều rộng quái
    int height_frame;
    int frame;

    int type_move;
    int animation_a;
    int animation_b;
    Input input_type;

    vector <BulletObject*> bullet_list;
};



#endif // THREATS_OBJECT_H_

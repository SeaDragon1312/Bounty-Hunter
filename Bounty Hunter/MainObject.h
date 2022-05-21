#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "common.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8           // trọng lực
#define MAX_FALL_SPEED 10           // trọng lực lớn nhất (có thể do lực cản không khí :D)
#define PLAYER_SPEED 8              // tốc độ nhân vật
#define PLAYER_JUMP_VAL 20          // lực nhảy của nhân vật

class MainObject : public BaseObject
{
public:
    MainObject();                   // hàm khởi tạo
    ~MainObject();                  // hàm hủy

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };
    bool LoadImg(string path, SDL_Renderer* screen);        // LoadImg từ MainObjec kế thừa từ BaseObject
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen); // tiếp nhận thông tin đầu vào từ chuột hoặc bàn phím
    void set_clips();

    void DoPlayer(Map& map_data);                       // thực hiện hành động nhân vật chính
    void CheckToMap(Map& map_data);                     // kiểm tra va chạm với map
    void SetMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}    // set giá trị biên của map
    void CenterEntityOnMap(Map& map_data);              // kéo map theo nhân vật
    void UpdateImagePlayer(SDL_Renderer* des);
    SDL_Rect GetRectFrame();
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    float get_x() const {return x_pos;}
    float get_y() const {return y_pos;}

    void Setxypos(const float& xpos, const float& ypos) {x_pos = xpos; y_pos = ypos;}

    void set_bullet_list(vector<BulletObject*> bullet_list){
        p_bullet_list = bullet_list;
    }
    vector<BulletObject*> get_bullet_list() const {return p_bullet_list;}
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);          // hàm xóa đạn
    void IncreaseMoney();
    void SetComebackTime(const int& cb_time) {come_back_time = cb_time;}
    int GetMoneyCount() const {return money_count;}

private:
    int money_count;    // đếm số lượng đồng xu

    vector<BulletObject*> p_bullet_list;

    float x_val;        // giá trị x thay đổi
    float y_val;        // giá trị y thay đổi

    float x_pos;        // giá trị x hiện tại
    float y_pos;        // giá trị y hiện tại

    int width_frame;    // chiều dài frame
    int height_frame;   // chiều cao frame

    SDL_Rect frame_clip[8];     // mảng 8 Rect(hcn)
    Input input_type;
    int frame;
    int status;                 // trạng thái WALK_NONE, WALK_LEFT, hoặc WALK_RIGHT
    bool on_ground;             // kiểm tra có trên mặt đất hay không

    int map_x_;                 // biến các mép của bản đồ (start_x)
    int map_y_;

    int come_back_time;         // xử dụng nếu rơi xuống vực
};

#endif // MAIN_OBJECT_H_

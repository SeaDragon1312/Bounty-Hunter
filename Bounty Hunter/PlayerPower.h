#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "common.h"
#include "BaseObject.h"

class PlayerPower : public BaseObject
{

public:
    PlayerPower();
    ~PlayerPower();

    void SetNum(const int& num) {number = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();
private:
    int number;
    vector<int> pos_list;

};

class PlayerMoney : public BaseObject
{

public:
    PlayerMoney();
    ~PlayerMoney();
    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos = x; y_pos = y;}
private:
    int x_pos;
    int y_pos;


};



#endif // PLAYER_POWER_H_

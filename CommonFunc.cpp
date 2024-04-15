#include "CommonFunc.h"
bool SDLCommonFunc::CheckCollisionMouse(int x, int y, const SDL_Rect& obj)
{
    int left_a = obj.x;                         // tọa độ đường đứng bên trái vật 1
    int right_a = obj.x + obj.w;            // tọa độ đường đứng bên phải vật 1
    int top_a = obj.y;                          // tọa độ đường ngang phía trên vật 1
    int bottom_a = obj.y + obj.h;           // tọa độ đường ngang phía dưới vật 1

    if (x >= left_a && x <= right_a && y <= bottom_a && y >= top_a) {
        return true;
    }
    else {
        return false;
    }
}
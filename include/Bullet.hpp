#pragma once
#include <SDL.h>

class Bullet {
public:
    Bullet(int x, int y);
    void update(float dt);
    void render(SDL_Renderer* ren);
    bool isAlive() const;
    SDL_Rect& getRect();

private:
    SDL_Rect rect;
    int speed = 500; // 像素/秒
    bool alive = true;
};

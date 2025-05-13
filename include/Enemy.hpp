#pragma once
#include <SDL.h>


class Enemy {
public:
    Enemy(SDL_Renderer* ren, const char* imgPath, int x, int y);  // ← 删掉大括号里的实现
    ~Enemy();
    void update(float dt);
    void render();
    bool isAlive() const;
    SDL_Rect getRect() const;

private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect;
    int speed = 100;
    bool alive = true;
};


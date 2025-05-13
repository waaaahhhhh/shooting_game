#pragma once
#include <SDL.h>
#include <vector>
#include "Bullet.hpp"

class Player {
public:
    Player(SDL_Renderer* ren, const char* imgPath);
    ~Player();
    void update(float dt);
    void render();
    SDL_Rect getRect() const;
    void handleEvent(const SDL_Event& e, std::vector<class Bullet*>& bullets);


private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect;
    int dx = 0;
    int dy = 0;
    int speed = 200;  // 像素/秒
};


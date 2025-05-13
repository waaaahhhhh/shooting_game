#include "Enemy.hpp"
#include <SDL_image.h>
#include <iostream>

Enemy::Enemy(SDL_Renderer* ren, const char* imgPath, int x, int y) {
    // 使用传入的 renderer 参数
    renderer = ren;

    auto surf = IMG_Load(imgPath);
    if (!surf) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    
    rect = {x, y, 64, 64}; // 初始位置
}

Enemy::~Enemy() { SDL_DestroyTexture(texture); }

void Enemy::update(float dt) {
    rect.x -= int(speed * dt); // 敌机向左移动
    if (rect.x < -64) alive = false;
}

void Enemy::render() {
    // 渲染敌机到屏幕
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Enemy::isAlive() const { return alive; }

SDL_Rect Enemy::getRect() const { return rect; }

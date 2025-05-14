#include "Bullet.hpp"
#include <SDL_image.h>

constexpr int BULLET_WIDTH = 16;
constexpr int BULLET_HEIGHT = 8;
constexpr int SCREEN_WIDTH = 800;

Bullet::Bullet(int x, int y) : rect{x, y, BULLET_WIDTH, BULLET_HEIGHT}, alive(true) {}

void Bullet::update(float dt) {
    rect.x += int(speed * dt);
    if (rect.x > SCREEN_WIDTH) alive = false;
}
SDL_Rect& Bullet::getRect() {
    return rect;
}

void Bullet::render(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // 白色子弹
    SDL_RenderFillRect(ren, &rect);
}

bool Bullet::isAlive() const { return alive; }


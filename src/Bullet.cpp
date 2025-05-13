#include "Bullet.hpp"
#include <SDL_image.h>

Bullet::Bullet(int x, int y) : rect{x, y, 16, 8} {}

void Bullet::update(float dt) {
    rect.x += int(speed * dt);
    if (rect.x > 800) alive = false;
}
SDL_Rect& Bullet::getRect() {
    return rect;
}

void Bullet::render(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // 白色子弹
    SDL_RenderFillRect(ren, &rect);
}

bool Bullet::isAlive() const { return alive; }


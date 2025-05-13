#include "Player.hpp"
#include <SDL_image.h>
#include <iostream>  // for std::cerr

Player::Player(SDL_Renderer* ren, const char* imgPath) {
    renderer = ren;

    auto surf = IMG_Load(imgPath);
    if (!surf) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    rect = {100, 100, 64, 64}; // 初始位置
}



Player::~Player() { SDL_DestroyTexture(texture); }

void Player::handleEvent(const SDL_Event& e, std::vector<Bullet*>& bullets) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
        bullets.push_back(new Bullet(rect.x + rect.w, rect.y + rect.h/2 - 4));
    }
    const Uint8* ks = SDL_GetKeyboardState(nullptr);
    dx = dy = 0;
    if (ks[SDL_SCANCODE_W]) dy = -1;
    if (ks[SDL_SCANCODE_S]) dy = +1;
    if (ks[SDL_SCANCODE_A]) dx = -1;
    if (ks[SDL_SCANCODE_D]) dx = +1;
}

void Player::update(float dt) {
    const Uint8* ks = SDL_GetKeyboardState(NULL);
    dx = dy = 0;
    if (ks[SDL_SCANCODE_W]) dy = -1;
    if (ks[SDL_SCANCODE_S]) dy = +1;
    if (ks[SDL_SCANCODE_A]) dx = -1;
    if (ks[SDL_SCANCODE_D]) dx = +1;

    rect.x += int(dx * speed * dt);
    rect.y += int(dy * speed * dt);
}

void Player::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect Player::getRect() const {
    return rect;
}


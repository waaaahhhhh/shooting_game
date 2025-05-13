#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

// 构造函数
Game::Game() {
    isRunning = false;
    window = nullptr;
    renderer = nullptr;
}

// 析构函数
Game::~Game() {
    clean();
}

// 初始化函数
bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // 一切成功，设置 running 状态
    isRunning = true;
    return true;
}


// 游戏主循环
void Game::run() {
    const float FPS = 60.0f;
    const float frameDelay = 1000.0f / FPS;

    Uint32 frameStart;
    float frameTime;

    while (isRunning) {
        frameStart = SDL_GetTicks();

        handleEvents();
        update(frameDelay / 1000.0f);
        render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
            SDL_Delay(Uint32(frameDelay - frameTime));
    }
}

// 清理资源
void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


void Game::handleEvents() {
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) isRunning = false;
        player->handleEvent(evt, bullets);
    }
}

void Game::update(float dt) {
    player->update(dt);
    if (rand() % 100 < 2) { // 每2%的概率生成敌机
        enemies.push_back(new Enemy(renderer, "assets/enemy.png", 800, rand()%536));
    }
    for (auto it = bullets.begin(); it != bullets.end();) {
        (*it)->update(dt);
        if (!(*it)->isAlive()) { delete *it; it = bullets.erase(it); }
        else ++it;
    }
    for (auto eit = enemies.begin(); eit != enemies.end();) {
        Enemy* e = *eit;
        e->update(dt);
        bool removed = false;
        if (!e->isAlive()) { removed = true; }
        else {
            SDL_Rect er = e->getRect();
            for (auto bit = bullets.begin(); bit != bullets.end(); ++bit) {
                if (SDL_HasIntersection(&er, &(*bit)->getRect())) {
                    score += 10;
                    delete *bit;
                    bullets.erase(bit);
                    removed = true;
                    break;
                }
            }
        }
        if (removed) { delete e; eit = enemies.erase(eit); }
        else ++eit;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    player->render();
    for (auto& b : bullets) b->render(renderer);
    for (auto& e : enemies) e->render();
    SDL_RenderPresent(renderer);
}


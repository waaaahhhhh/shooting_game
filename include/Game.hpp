#pragma once
#include <SDL.h>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <SDL_image.h>   // ← 解决 IMG_Load
#include <iostream>      // ← 解决 std::cerr / std::endl

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int w, int h);
    void run();
    void clean();
private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning = false;
    Player* player = nullptr;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    int score = 0;
};

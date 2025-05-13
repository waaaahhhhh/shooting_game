#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"
#include <iostream>


int main(int argc, char* argv[]) {
    // 初始化 SDL2 和图片库
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 初始化 SDL_image 库（用于加载 PNG、JPG 等格式）
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    // 创建并初始化游戏实例
    Game game;
    if (!game.init("2D Shooting Game", 800, 600)) {
        std::cerr << "Game initialization failed!" << std::endl;
        return 1;
    }

    // 运行游戏
    game.run();

    // 退出之前清理资源
    game.clean();

    // 退出 SDL 和 SDL_image 库
    IMG_Quit();
    SDL_Quit();

    return 0;
}

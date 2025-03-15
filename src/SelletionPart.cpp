#include "Game.h"
#include "Const.h"

std::vector<int> Game::initSelection()
{
    // tạo 2 id cho chế độ 2 người
    std::vector<int> ID(2, 0);

    // chờ cho đến khi chọn được 2 nhân vật
    while (!handleEvent(ID[0]))
    {
        destRect.x = SELECT_X + (ID[0] % AVATAR_COL) * SELECT_W;
        destRect.y = SELECT_Y + (ID[0] / AVATAR_COL) * SELECT_H;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, selectTexture, NULL, &destRect);
        SDL_RenderPresent(renderer);
    }
    destRect.x = SELECT_X;
    destRect.y = SELECT_Y;
    while (!handleEvent(ID[1]))
    {
        destRect.x = SELECT_X + (ID[1] % AVATAR_COL) * SELECT_W;
        destRect.y = SELECT_Y + (ID[1] / AVATAR_COL) * SELECT_H;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, selectTexture, NULL, &destRect);
        SDL_RenderPresent(renderer);
    }
    return ID;
}


bool Game::handleEvent(int& id)
{
    // xử lí các ấn thoát và di chuyển giữa các ô
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            SDL_Quit();
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_d:
                playSound(2);
                id += 1;
                if (id >= (AVATAR_ROW * AVATAR_COL - 1))
                    id = AVATAR_ROW * AVATAR_COL - 1;
                break;
            case SDLK_a:
                playSound(2);
                id -= 1;
                if (id < 0)
                    id = 0;
                break;
            case SDLK_w:
                playSound(2);
                id -= AVATAR_COL;
                if (id < 0)
                    id += AVATAR_COL;
                break;
            case SDLK_s:
                playSound(2);
                id += AVATAR_COL;
                if (id >= (AVATAR_ROW * AVATAR_COL - 1))
                    id -= AVATAR_COL;
                break;
            case SDLK_j:
                playSound(3);
                return true;
            default:
                break;
            }
        }
    }
    return false;
}
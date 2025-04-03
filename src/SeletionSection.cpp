#include "Game.h"
#include "Const.h"
#include "SelectionSection.h"
#include "TextureManager.h"

// Khởi tạo các biến tĩnh
SDL_Texture* SelectionSection::background = TextureManager::LoadTexture(SELECT_BG_IMG);
SDL_Texture* SelectionSection::selectTexture = TextureManager::LoadTexture(SELECT_FRAME_IMG);
SDL_Rect SelectionSection::destRect = { SELECT_X, SELECT_Y, SELECT_W, SELECT_H };

SelectionSection::SelectionSection()
{
    
}

SelectionSection::~SelectionSection()
{

}

void SelectionSection::selectionLoad()
{
	background = TextureManager::LoadTexture(SELECT_BG_IMG);
	selectTexture = TextureManager::LoadTexture(SELECT_FRAME_IMG);
	destRect = { SELECT_X, SELECT_Y, SELECT_W, SELECT_H };
}

std::vector<int> SelectionSection::Selection(int players)
{
    // tạo 2 id cho chế độ 2 người
    std::vector<int> ID(players, 0);

    // chờ cho đến khi chọn được nhân vật
    for (int i = 0; i < players; i++)
    {
        while (!handleEvent(ID[i]))
        {
            destRect.x = SELECT_X + (ID[i] % AVATAR_COL) * SELECT_W;
            destRect.y = SELECT_Y + (ID[i] / AVATAR_COL) * SELECT_H;
            SDL_RenderClear(Game::renderer);
            SDL_RenderCopy(Game::renderer, background, NULL, NULL);
            SDL_RenderCopy(Game::renderer, selectTexture, NULL, &destRect);
            SDL_RenderPresent(Game::renderer);
        }
        destRect.x = SELECT_X;
        destRect.y = SELECT_Y;
    }
    return ID;
}


bool SelectionSection::handleEvent(int& id)
{
    // xử lí các ấn thoát và di chuyển giữa các ô
    while (SDL_PollEvent(&Game::event))
    {
        if (Game::event.type == SDL_QUIT)
            SDL_Quit();
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_d:
                Game::playSound(2);
                id += 1;
                if (id >= (AVATAR_ROW * AVATAR_COL - 1))
                    id = AVATAR_ROW * AVATAR_COL - 1;
                break;
            case SDLK_a:
                Game::playSound(2);
                id -= 1;
                if (id < 0)
                    id = 0;
                break;
            case SDLK_w:
                Game::playSound(2);
                id -= AVATAR_COL;
                if (id < 0)
                    id += AVATAR_COL;
                break;
            case SDLK_s:
                Game::playSound(2);
                id += AVATAR_COL;
                if (id >= (AVATAR_ROW * AVATAR_COL - 1))
                    id -= AVATAR_COL;
                break;
            case SDLK_j:
                Game::playSound(3);
                return true;
            default:
                break;
            }
        }
    }
    return false;
}
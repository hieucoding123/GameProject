#include <iostream>
#include <SDL.h>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING); // Khởi tạo mọi thứ (video, hình ảnh, ... )

	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	// tạo cửa sổ ở giữa màn hình

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	// tạo trình dựng

	SDL_SetRenderDrawColor(renderer, 255, 200, 200, 255); // tô màu rgb và alpha
	SDL_RenderClear(renderer); // xóa trình dựng trước đó bằng màu ở trên
	SDL_RenderPresent(renderer);

	SDL_Delay(1000);	// Thời gian show cửa sổ

	return 0;
}
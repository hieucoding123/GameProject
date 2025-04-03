#pragma once

#include "SDL.h"
#include <vector>

// Lớp chứa phần chọn nhân vật

class SelectionSection
{
public:
	SelectionSection();
	~SelectionSection();
	/*
	* Tải destRect và các texture cần thiết
	*/
	static void selectionLoad();
	/*
	* Khởi tạo phần chọn nhân vật
	* @param players số nhân vật cần
	* @return một vector chứa các ID của nhân vật được chọn
	*/
	static std::vector<int> Selection(int players);

	/*
	* Xử lý sự kiện nhấn chuột, di chuyển giữa các ô
	* @param id ID của nhân vật sắp được chọn
	* @return true nếu đã chọn xong
	*/
	static bool handleEvent(int& id);
private:
	static SDL_Texture* background;
	static SDL_Texture* selectTexture;
	static SDL_Rect destRect;
};
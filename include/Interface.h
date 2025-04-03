#pragma once

#include <SDL.h>

// Giao diện game
class Interface
{
public:
	Interface();
	~Interface();
	void init();

	/*
	* @return true nếu chọn thành công
	*/
	bool success() const { return chooseSuccess; }

	/*
	* Chọn chế độ chơi
	* @return 0 nếu solo, 1 nếu sinh tồn
	*/
	int selectMode();

	/*
	* Chọn số người chơi
	* @return 1 nếu 1 người, 2 nếu 2 người
	*/
	int selectNumOfPlayers();
private:
	void draw();

	SDL_Texture* interfaceTex;
	SDL_Texture* buttonsTex;
	SDL_Rect srcBut1, destBut1;
	SDL_Rect srcBut2, destBut2;

	// chế độ chơi
	int mode;
	// số người chơi
	int players;

	bool chooseSuccess = true;
};
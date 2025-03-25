#pragma once

#include "SDL.h"
#include <vector>
#include <memory>
#include "AudioManager.h"

class Tile;
class EffectManager;
class GameObject;

// Lớp chứa phần vào chơi game
class PlaySection
{
public:
	PlaySection();
	~PlaySection();

	/*
	* Tải các biến tĩnh
	*/
	static void playLoad();

	/*
	* Khởi tạo nhân vật thông qua ID
	* @param ID vector chứa ID của nhân vật
	*/
	void init(std::vector<int> ID);

	/*
	* Xử lý sự kiện
	*/
	void handleEvents();

	/*
	* Cập nhật phần chơi
	*/
	void update();

	/*
	* Vẽ các thành phần trong phần chơi
	*/
	void render();

	/*
	* Hủy các thành phần trong phần chơi
	*/
	void clean();

	/*
	* Cài đặt và khởi tạo nhân vật qua ID
	* @param ID ID của nhân vật
	* @param xpos vị trí x đặt nhân vật
	* @param ypos vị trí y đặt nhân vật
	* @param camera có camera không
	*/
	void setCharacter(const int& ID, int xpos, int ypos, bool camera);

	/*
	* Kiểm tra xem phần chơi còn chạy không
	*/
	bool playing() const { return isPlaying; };

	void setPlaying(bool b) { isPlaying = b; };

	static std::vector<std::unique_ptr<Tile>> tiles;
	static SDL_Rect camera;
	static EffectManager effectManager;
	static int MAP_SCALE;
	static std::vector<GameObject*> gameObjects;
	/*
	* Kiểm tra hai hình chữ nhật giao nhau
	* @param rect1 hình chữ nhật đầu tiên
	* @param rect2 hình chữ nhật thứ hai
	* @return true nếu hai hình giao nhau
	*/
	static bool AABB(const SDL_Rect& rec1, const SDL_Rect& rec2);

	/*
	* Yêu cầu điều chỉnh camera trên trục x
	* @param x quãng đường di chuyển trên trục x
	*/

	static void setCameraX(int x);
	/*
	* Yêu cầu điều chỉnh camera trên trục y
	* @param y quãng đường di chuyển trên trục y
	*/
	static void setCameraY(int y);
private:
	/*
	* Kiểm tra va cham giữa các đối tượng
	*/
	//void objectCollision();

	bool isPlaying = true;
};
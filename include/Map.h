#pragma once
#include <vector>
#include <memory>

class Tile;

class Map
{
public:
	Map();
	~Map();
	/*
	* Tải map, cài đặt tile
	* @param path đường dẫn đến file txt
	*/
	void LoadMap(const char* path);

	/*
	* Cập nhật map
	*/
	void update();

	/*
	* Vẽ map
	*/
	void draw();

	/*
	* Dọn dẹp map
	*/
	void clean();
private:
	std::vector<std::unique_ptr<Tile>> tiles;
};
#pragma once
class Tilemap {
private:
	static int mapCols, mapRows;
	static int tileSize;

public:
	Tilemap();
	~Tilemap();

	void tick();
	void render();
};


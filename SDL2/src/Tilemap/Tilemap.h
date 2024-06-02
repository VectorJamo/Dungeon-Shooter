#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Tilemap {
private:
	static const int mapCols = 54, mapRows = 54;
	static const int tileSize = 32;

	unsigned char** tileMap;

	SDL_Texture* brickTexture;

private:
	void loadTileMap(const char* filePath);

public:
	Tilemap(const char* filePath);
	~Tilemap();

	void tick();
	void render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight);

	inline unsigned char** getTileMap() { return tileMap; } // Cast this return type to unsigned char** to access the values.
	inline int getTileSize() { return tileSize; }
	inline int getMapRows() { return mapRows; }
	inline int getMapCols() { return mapCols; }
};


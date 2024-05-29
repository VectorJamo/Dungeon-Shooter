#include "Tilemap.h"

#include "../graphics/Display.h"

#include <iostream>
#include <fstream>
#include <string>

Tilemap::Tilemap(const char* filePath) {
	tileMap = new unsigned char*[mapRows];
	for (int i = 0; i < mapRows; i++) {
		tileMap[i] = new unsigned char[mapCols];
	}

	loadTileMap(filePath);
	brickTexture = IMG_LoadTexture(Display::getRendererInstance(), "res/images/Bricks.png");
}

Tilemap::~Tilemap() {
	for (int i = 0; i < mapRows; i++) {
		delete[] tileMap[i];
	}
	delete[] tileMap;

	SDL_DestroyTexture(brickTexture);
}

void Tilemap::tick() {
}

void Tilemap::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight) {
	for (int i = 0; i < mapRows; i++) {
		for (int j = 0; j < mapCols; j++) {
			if (tileMap[i][j] != '0') {
				int tileWorldX = j*tileSize;
				int tileWorldY = i*tileSize;
				int tileScreenX = tileWorldX - ((playerWorldX + playerWidth/2) - Display::getScreenWidth()/2);
				int tileScreenY = tileWorldY - ((playerWorldY + playerHeight/2)- Display::getScreenHeight()/2);
				
				SDL_Rect src = { 0, 0, tileSize, tileSize };
				SDL_Rect dest = { tileScreenX, tileScreenY, tileSize, tileSize };

				SDL_RenderCopy(Display::getRendererInstance(), brickTexture, &src, &dest);
			}
		}
	}
}

void Tilemap::loadTileMap(const char* filePath) {
	std::ifstream stream(filePath);

	std::string line;
	int row = 0, col = 0;
	while (std::getline(stream, line)) {
		for (char& c : line) {
			if (c != '\t') { 
				tileMap[row][col] = c;
				col++;
			}
		}
		row++;
		col = 0;
	}
}

#pragma once

#include "Entity.h"
#include "../tilemap/Tilemap.h"
#include <vector>

struct ActiveLazer {
	int lazerWorldX, lazerWorldY;
	char lazerDirection;
};

class Laser: public Entity {
private:
	SDL_Texture* entityImage2;
	int lazerSpeed;
	std::vector<ActiveLazer*> lazers;
	
public:
	Laser(const char* path, const char* path2, float x, float y, int width, int height, Tilemap* map);
	~Laser();

	void tick() override;
	void render() override;

	void tick(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char& direction);
	void render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char& direction);
};


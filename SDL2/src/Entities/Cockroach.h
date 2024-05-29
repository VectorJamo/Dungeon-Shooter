#pragma once
#include "Entity.h"
#include "../tilemap/Tilemap.h"

class Cockroach: public Entity {
private:
	Tilemap* map;

	SDL_Rect roachLeft, roachRight, roachUp, roachDown;
	SDL_Rect currentClipRect;

	float dx, dy;
	char directions[4] = { 'U', 'D', 'L', 'R' };
	char direction = 'D';
	float speed;
	int directionCounter;

public:
	Cockroach(const char* path, float x, float y, int width, int height, Tilemap* map, char direction = 'D');
	~Cockroach();

	void tick() override;
	void render() override;
	void render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight);
};


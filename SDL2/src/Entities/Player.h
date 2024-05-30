#pragma once

#include "Entity.h"
#include "../tilemap/Tilemap.h"

class Player: public Entity {
private:
	Tilemap* map;

	SDL_Rect* leftClipRects, *rightClipRects, *upClipRects, *downClipRects;
	SDL_Rect currentClipRect;

	float dx, dy;
	float speed;
	char direction = 'D';

	float animationCounter = 0.0f;

private:
	void playAnimation();

public:
	Player(const char* path, float x, float y, int width, int height, Tilemap* map);
	~Player();

	void setCurrentClipRect(SDL_Rect rect);

	void tick() override;
	void render() override;

	inline char getDirection() { return direction; }
};


#pragma once

#include "Entity.h"
#include "../tilemap/Tilemap.h"
#include <vector>

struct ActiveLazer {
	int lazerWorldX, lazerWorldY;
	char lazerDirection;
};

struct LaserAnimation {
	SDL_Rect* currentClipRect;
	static SDL_Texture* animationSprite;

	int animationWorldX, animationWorldY;
	
	int animationSpeed = 2;
	int animationCounter = 0;	
	int currentFrame = 0;
	int maxFrames = 11;
};

class Laser: public Entity {
private:
	Tilemap* map;
	SDL_Texture* entityImage2;
	int lazerSpeed;
	static std::vector<ActiveLazer*> lazers;

	int lazerTimer;
	bool canShoot;

	SDL_Rect* animationClipRects;
	std::vector<LaserAnimation*> animations;

public:
	static bool hasShot;

public:
	Laser(const char* path, const char* path2, float x, float y, int width, int height, Tilemap* map);
	~Laser();

	void tick() override;
	void render() override;

	static void addLaser(int worldX, int worldY, char direction);
	void tick(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char direction);
	void render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char direction);
};


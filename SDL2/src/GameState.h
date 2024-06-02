#pragma once
#include "StateManager.h"
#include "tilemap/Tilemap.h"

#include "entities/Player.h"
#include "entities/Cockroach.h"
#include "entities/Laser.h"
#include "entities/AnotherPlayer.h"

#include <vector>

class GameState: public StateManager {
private:
	Tilemap* map;
	Player* player;
	std::vector<Cockroach*> roaches;
	Laser* lasers;
	
	bool isServer;
	AnotherPlayer* anotherPlayer;

public:
	GameState(bool isServer);
	~GameState();

	void handleInput(SDL_Event& ev) override;
	void tick() override;
	void render() override;
};


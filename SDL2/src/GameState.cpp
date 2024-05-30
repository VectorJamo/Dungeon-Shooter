#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

GameState::GameState() {
	map = new Tilemap("res/maps/dungeon.txt");

	player = new Player("res/images/Soldier-Blue.png", map->getTileSize()*38, map->getTileSize()*38, 64, 64, map);
	player->setCollisionRect(20, 20, 30, 30);


	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'D'));
	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'U'));
	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'L'));
	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'R'));

	lasers = new Laser("res/images/laser_vertical.png", "res/images/laser_horizontal.png", 0, 0, 16, 16, map);
}

GameState::~GameState() {
	delete map;
	delete player;
}

void GameState::handleInput(SDL_Event& ev) {

}

void GameState::tick() {
	map->tick();
	player->tick();

	for(Cockroach*& roach: roaches)
		roach->tick();

	lasers->tick(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight(), player->getDirection());
}

void GameState::render() {
	map->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight());
	player->render();
	for(Cockroach*& roach: roaches)
		roach->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight());

	lasers->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight(), player->getDirection());
}
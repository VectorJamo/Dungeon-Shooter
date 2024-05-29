#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

GameState::GameState() {
	map = new Tilemap("res/maps/dungeon.txt");

	player = new Player("res/images/Soldier-Blue.png", map->getTileSize()*38, map->getTileSize()*38, 64, 64, map);
	player->setCollisionRect(20, 20, 30, 30);
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
}

void GameState::render() {
	map->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight());
	player->render();
}
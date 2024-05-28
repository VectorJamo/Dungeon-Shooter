#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

GameState::GameState() {
	map = new Tilemap("res/maps/dungeon.txt");

	player = new Player("res/images/Soldier-Blue.png", 64, 64, 32, 32, map);
}

GameState::~GameState() {


}

void GameState::handleInput(SDL_Event& ev) {

}

void GameState::tick() {
	
	map->tick();
	player->tick();

}

void GameState::render() {
	map->render();
	player->render();
}
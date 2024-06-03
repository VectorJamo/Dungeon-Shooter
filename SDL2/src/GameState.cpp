#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

#include "networking/Client.h"
#include "networking/Server.h"

GameState::GameState(bool isServer) {
	this->isServer = isServer;
	map = new Tilemap("res/maps/dungeon.txt");

	player = new Player("res/images/Soldier-Blue.png", map->getTileSize()*10, map->getTileSize()*30, 64, 64, map);
	player->setCollisionRect(20, 20, 30, 30);

	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'D'));
	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'U'));
	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'L'));
	roaches.emplace_back(new Cockroach("res/images/roach.png", map->getTileSize() * 30, map->getTileSize() * 30, 32, 32, map, 'R'));

	lasers = new Laser("res/images/laser_vertical.png", "res/images/laser_horizontal.png", 0, 0, 16, 16, map);

	anotherPlayer = new AnotherPlayer("res/images/Soldier-Red.png", 0, 0, 64, 64);
	if (isServer) {
		Server::setCurrentPlayerState(player->getXPos(), player->getYPos(), 100, false, 'D');
	}
	else {
		Client::setCurrentPlayerState(player->getXPos(), player->getYPos(), 100, false, 'D');
	}
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
	anotherPlayer->tick();
	
	if (isServer) {
		Server::setCurrentPlayerState(player->getXPos(), player->getYPos(), 100, false, player->getDirection());
		anotherPlayer->setXPos(Server::getAnotherPlayerInfo().x);
		anotherPlayer->setYPos(Server::getAnotherPlayerInfo().y);
		anotherPlayer->setDirection(Server::getAnotherPlayerInfo().direction);
		anotherPlayer->hasShot = Server::getAnotherPlayerInfo().hasShot;
	}
	else {
		Client::setCurrentPlayerState(player->getXPos(), player->getYPos(), 100, false, player->getDirection());
		anotherPlayer->setXPos(Client::getAnotherPlayerInfo().x);
		anotherPlayer->setYPos(Client::getAnotherPlayerInfo().y);
		anotherPlayer->setDirection(Client::getAnotherPlayerInfo().direction);
		anotherPlayer->hasShot = Client::getAnotherPlayerInfo().hasShot;
	}
	Light::lightWorldX = player->getXPos() + player->getWidth()/2;
	Light::lightWorldY = player->getYPos() + player->getHeight()/2;
}

void GameState::render() {
	map->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight());
	player->render();
	for(Cockroach*& roach: roaches)
		roach->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight());

	lasers->render(player->getXPos(), player->getYPos(), player->getWidth(), player->getHeight(), player->getDirection());
	anotherPlayer->render(player->getXPos(), player->getYPos());
}
#include "Game.h"
#include <iostream>
#include "utils/Macros.h"

bool Game::running;
bool Game::isClient;
bool Game::isServer;
Game::Game(int width, int height, const char* title) {
	running = true;

	char ans;
	std::cout << "Type H if you want to host a game or J if you want to join a game." << std::endl;
	std::cin >> ans;

	if (ans == 'H') {
		isServer = true;
		isClient = false;
	}
	else {
		isClient = true;
		isServer = false;
	}

	if (isClient) {
		char ip[256];
		int port;
		std::cout << "Enter the ip address of the remote host." << std::endl;
		std::cin >> ip;
		std::cout << "Enter the port number where the remote host is listening for a client." << std::endl;
		std::cin >> port;

		std::cout << ip << std::endl;
		std::cout << port << std::endl;

		// TODO: Create the Client Socket Object
		Client::createClient(ip, port);
		networkingThread = new std::thread(Client::startUpClient);
	}
	else {
		// Create the server socket object
		Server::createServer();
		networkingThread = new std::thread(Server::startUpServer);

	}
	display = new Display(width, height, title);

	gameState = new GameState(isServer);
	StateManager::currentState = gameState;
}

Game::~Game() {
	delete gameState;
	delete display;
}

void Game::run() {
	while (running) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				running = false;

			StateManager::currentState->handleInput(ev);
		}

		// Clear the screen
		display->clear(10, 10, 10, 255);
		
		// Tick
		StateManager::currentState->tick();

		// Draw
		StateManager::currentState->render();

		// Swap buffers
		display->show();

		limitFPS();
	}
}
void Game::limitFPS() {
	float deltaTime = SDL_GetTicks() - lastTime;
	if (deltaTime < 1000.0f / FPS) {
		SDL_Delay((1000.0f / FPS) - deltaTime);
	}
	lastTime = SDL_GetTicks();
}

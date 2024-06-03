#include "Client.h"
#include "../utils/Macros.h"
#include "../Game.h"
#include "../entities/Laser.h"

#include <iostream>

WSAData Client::data;
WORD Client::version;
SOCKET Client::clientSocket;
sockaddr_in Client::serverInfo;
int Client::serverInfoLength;
bool Client::isClient;

StateInfo Client::currentPlayer;
StateInfo Client::anotherPlayer;

void Client::createClient(char* ip, int port) {
	// Initialize Winsock
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0) {
		DEBUG_LOG("Cannot initialize winsock.");
	}

	// Store the server's info
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(port);
	serverInfoLength = sizeof(sockaddr_in);

	// Convert the ip from text to the sin_addr struct
	inet_pton(AF_INET, ip, &serverInfo.sin_addr);

	// Create the client socket
	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
}

void Client::startUpClient() {
	const char* message = "CON-REQ";

	int sendOk = sendto(clientSocket, message, strlen(message) + 1, 0, (sockaddr*)&(serverInfo), sizeof(sockaddr));
	if (sendOk == SOCKET_ERROR) {
		std::cout << WSAGetLastError() << std::endl;
		DEBUG_LOG("Failed to send message to the server.");
	}
	std::cout << "Connection request message sent to the server." << std::endl;

	// Create a buffer to store the data coming in from the server
	char buffer[1024];

	// Create a buffer to send the data to the server
	char sendBuffer[1024];
	while (Game::running) {
		// Clear the buffer
		ZeroMemory(buffer, 1024);

		// TODO: Send game state data to the server
		int sendOk = sendto(clientSocket, (char*)&currentPlayer, sizeof(StateInfo), 0, (sockaddr*)(&serverInfo), sizeof(sockaddr));
		if (sendOk == SOCKET_ERROR) {
			std::cout << WSAGetLastError() << std::endl;
			DEBUG_LOG("Error sending game state data to the client.");
		}

		// TODO: Parse the incoming data from server
		int bytesIn = recvfrom(clientSocket, (char*)&anotherPlayer, sizeof(StateInfo), 0, (sockaddr*)&serverInfo, &serverInfoLength);
		if (anotherPlayer.hasShot) {
			anotherPlayer.hasShot = false;
			Laser::addLaser(anotherPlayer.x, anotherPlayer.y, anotherPlayer.direction);
		}

		std::cout << "Another player info:" << std::endl;
		std::cout << "X: " << anotherPlayer.x << std::endl;
		std::cout << "Y: " << anotherPlayer.y << std::endl;
	}
}

void Client::cleanUpClient() {
	closesocket(clientSocket);
	WSACleanup();
}

void Client::forceSendPlayerState() {
	int sendOk = sendto(clientSocket, (char*)&currentPlayer, sizeof(StateInfo), 0, (sockaddr*)(&serverInfo), sizeof(sockaddr));
	if (sendOk == SOCKET_ERROR) {
		std::cout << WSAGetLastError() << std::endl;
		DEBUG_LOG("Error sending game state data to the client.");
	}
}

void Client::setCurrentPlayerState(int x, int y, int health, bool hasShot, char direction) {
	currentPlayer.x = x;
	currentPlayer.y = y;
	currentPlayer.health = health;
	currentPlayer.hasShot = hasShot;
	currentPlayer.direction = direction;
}

StateInfo Client::getAnotherPlayerInfo() {
	return anotherPlayer;
}

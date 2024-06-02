#include "Server.h"
#include <iostream>
#include "../utils/Macros.h"

#include "../Game.h"

#pragma comment (lib, "ws2_32.lib")

#define LOCAL_HOST_ADDRESS "172.0.0.1"
#define PORT 12000

WSAData Server::data;
WORD Server::version;
SOCKET Server::serverSocket;
sockaddr_in Server::serverInfo;
sockaddr_in Server::clientInfo;
int Server::clientInfoLength;
bool Server::firstConnect = true;

StateInfo Server::currentPlayer;
StateInfo Server::anotherPlayer;

void Server::createServer() {
	// Initialize Winsock
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0) {
		DEBUG_LOG("Cannot initialize winsock.");
	}

	// Bind the socket to the ip address and port
	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

	serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(PORT);

	if (bind(serverSocket, (sockaddr*)&serverInfo, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		std::cout << WSAGetLastError() << std::endl;
		DEBUG_LOG("Failed to bind the socket to the specified ip and port.");
	}

	// Clear the memory where we will store the incoming client's address and port info
	ZeroMemory(&clientInfo, sizeof(sockaddr_in));
	clientInfoLength = sizeof(sockaddr_in);
}

void Server::startUpServer() {
	// Create a buffer to store the data coming in from the client
	char buffer[1024];

	// Create a buffer tosend the data to the client
	char sendBuffer[1024];
	while (Game::running) {
		// Clear the buffer
		ZeroMemory(buffer, 1024);
		
		if (firstConnect) {
			firstConnect = false;
			std::cout << "Server is listening for a remote client." << std::endl;

			// Wait for client's message
			int bytesIn = recvfrom(serverSocket, buffer, 1024, 0, (sockaddr*)&clientInfo, &clientInfoLength);
			if (bytesIn == SOCKET_ERROR) {
				std::cout << "Error receiving info from client." << std::endl;
				continue;
			}
			// Display the message and client's info
			char clientIp[256];
			ZeroMemory(clientIp, 256);

			inet_ntop(AF_INET, &clientInfo.sin_addr, clientIp, 256);

			std::cout << "New client connected." << std::endl;
			std::cout << "Client address: " << clientIp << std::endl;
			std::cout << "Message: " << buffer << std::endl;
		}
		else {
			// TODO: Send game state data to the client
			std::cout << "Sent the server's player's info" << std::endl;
			int sendOk = sendto(serverSocket, (char*)&currentPlayer, sizeof(StateInfo), 0, (sockaddr*)(&clientInfo), sizeof(sockaddr));
			if (sendOk == SOCKET_ERROR) {
				std::cout << WSAGetLastError() << std::endl;
				DEBUG_LOG("Error sending game state data to the client.");
			}

			// TODO: Parse the incoming data from client
			int bytesIn = recvfrom(serverSocket, (char*)&anotherPlayer, sizeof(StateInfo), 0, (sockaddr*)&clientInfo, &clientInfoLength);
			std::cout << "Got the client's player's info" << std::endl;

			std::cout << "Another player info:" << std::endl;
			std::cout << "X: " << anotherPlayer.x << std::endl;
			std::cout << "Y: " << anotherPlayer.y << std::endl;
		}
	}
}

void Server::cleanUpServer() {
	closesocket(serverSocket);
	WSACleanup();
}

void Server::setCurrentPlayerState(int x, int y, int health, bool hasShot, char direction) {
	currentPlayer.x = x;
	currentPlayer.y = y;
	currentPlayer.health = health;
	currentPlayer.hasShot = hasShot;
	currentPlayer.direction = direction;
}

StateInfo Server::getAnotherPlayerInfo(){
	return anotherPlayer;
}

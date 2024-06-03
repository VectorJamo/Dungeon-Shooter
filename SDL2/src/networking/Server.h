#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS	
#include <WS2tcpip.h>

#include "StateInfo.h"

class Server {
private:
	static WSAData data;
	static WORD version;

	static SOCKET serverSocket;
	static sockaddr_in serverInfo;
	static sockaddr_in clientInfo;
	static int clientInfoLength;
	static bool firstConnect;


public:
	static bool isServer;
	static bool hasActiveClient;
	static int shotCounter;

	// Another player's state information 
	static StateInfo anotherPlayer;
	// Current player's state information 
	static StateInfo currentPlayer;

public:
	static void createServer();
	static void startUpServer();
	static void cleanUpServer();
	static void forceSendPlayerState();

	static void setCurrentPlayerState(int x, int y, int health, bool hasShot, char direction);

	static StateInfo getAnotherPlayerInfo();
};

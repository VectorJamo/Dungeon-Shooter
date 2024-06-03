#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS	
#include <WS2tcpip.h>

#include "StateInfo.h"

class Client {
private:
	static WSAData data;
	static WORD version;

	static SOCKET clientSocket;
	static sockaddr_in serverInfo;
	static int serverInfoLength;

public:
	static bool isClient;
	// Another player's state information 
	static StateInfo anotherPlayer;
	// Current player's state information 
	static StateInfo currentPlayer;

public:
	static void createClient(char* ip, int port);
	static void startUpClient();
	static void cleanUpClient();
	static void forceSendPlayerState();

	static void setCurrentPlayerState(int x, int y, int health, bool hasShot, char direction);

	static StateInfo getAnotherPlayerInfo();
};


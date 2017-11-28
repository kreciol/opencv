#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

class MySender
{
private:
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

public:
	MySender();
	~MySender();

	int initialize();
	int connectToServer();
	int sendMessage(const char* message);

	void close();
};


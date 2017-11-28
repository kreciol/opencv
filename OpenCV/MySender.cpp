#include "MySender.h"


MySender::MySender()
{
}


MySender::~MySender()
{
}

int MySender::initialize()
{
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	return 0;
}

int MySender::connectToServer()
{
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8081);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");
}

int MySender::sendMessage(const char* message)
{
	//add end of message marker
	char toSendMessage[256];
	int size = strlen(message);
	for (int i = 0; i < size; i++) {
		toSendMessage[i] = message[i];
	}
	toSendMessage[size] = '@';
	toSendMessage[size + 1] = '\0';

	size = strlen(toSendMessage);
	if (send(s, toSendMessage, size, 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	return 0;
}

void MySender::close()
{
	printf("\nClosing Winsock...");
	closesocket(s);
	WSACleanup();
}

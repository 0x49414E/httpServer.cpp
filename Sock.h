#ifndef SOCK
#define SOCK

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

class Sock
{
public:
	Sock(const char* host, unsigned short port);
	~Sock();

	bool DLLInitialization();
	bool CreateSocket();
	virtual void Connect() = 0;
	void Cleanup();

	unsigned short GetPort() const;
	SOCKET& GetServerSocket();
	const char* GetHost() const;
protected:
	sockaddr_in service;
private:
	WSADATA wsaData;
	const char* host;
	unsigned short port;
	SOCKET serverSocket;
};

#endif
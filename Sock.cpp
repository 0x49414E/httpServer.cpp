#include "Sock.h"

Sock::Sock(const char* host, unsigned short port) : port(port), serverSocket(INVALID_SOCKET), host(host) {};
Sock::~Sock() { Cleanup(); }

bool Sock::DLLInitialization()
{
	// Initializing WS2_32.dll using the function WSAStartup()
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Checking for errors
	if (result != 0)
	{
		std::cout << "WSAStartup() Failed: " << result << std::endl;
		return false;
	}

	// Printing the status of the WinSock DLL
	std::cout << "WinSock DLL status: " << wsaData.szSystemStatus << std::endl;
	return true;
}

bool Sock::CreateSocket()
{
	// Initializing the socket using socket() function
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Checking for errors during initialization
	if (serverSocket == INVALID_SOCKET)
	{
		WSACleanup();
		std::cout << "Error at socket() func: " << WSAGetLastError() << std::endl;
		return false;
	}

	// Printing the status
	std::cout << "Socket initialized" << std::endl;
	return true;
}

void Sock::Cleanup()
{
	closesocket(serverSocket);
	WSACleanup();
}

unsigned short Sock::GetPort() const { return port; }
SOCKET& Sock::GetServerSocket() { return serverSocket; }
const char* Sock::GetHost() const { return host; }
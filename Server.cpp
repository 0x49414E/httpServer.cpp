#include "Server.h"
#include <sstream>

Server::Server(const char* host, unsigned short port) : Sock::Sock(host, port), addrlen(sizeof(service)), response(GenerateResponse()) {};

Server::~Server() {
	Cleanup();
}

bool Server::BindSocket()
{
	service.sin_family = AF_INET;
	service.sin_port = htons(GetPort());
	InetPton(AF_INET, (PCWSTR)GetHost(), &(service.sin_addr.s_addr));

	// Binding the socket to the port and the IP address
	// Checking for errors
	if (bind(GetServerSocket(), (SOCKADDR*)&service, addrlen) == SOCKET_ERROR)
	{
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		Cleanup();
		return false;
	}
	std::cout << "Binding socket" << std::endl;
	return true;
}

bool Server::Listen(int backlog)
{
	if (listen(GetServerSocket(), backlog) == SOCKET_ERROR) // listen(socket s, int backlog)  Backlog being the maximum number of connections expected
	{
		std::cout << "Error on listen(): " << WSAGetLastError() << std::endl;
		Cleanup();
		return false;
	}
	std::cout << "Listening on port " << GetPort() << std::endl;
	return true;
}


void Server::Connect() 
{
	while (1)
	{
		if ((clientSock = accept(GetServerSocket(), (SOCKADDR*)&service, (socklen_t*)&addrlen)) < 0)
		{
			std::cout << "\nConnection failed!\n";
		}
		const int size = 30270;
		char* buffer = new char[size] {0};
		int bytes = recv(clientSock, buffer, size, 0);
		std::cout << "Data received: \n" << buffer << std::endl;
		delete[] buffer;
		buffer = nullptr;
		send(clientSock, response.c_str(), response.size(), 0);
		closesocket(clientSock);
	}
}

std::string Server::GenerateResponse()
{
	std::string html = "<!DOCTYPE html><html lang=\"en\"><body><h1> Static HTTP Server </h1><p> Hello World! </p></body></html>";
	std::ostringstream ss;
	ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << html.size() << "\n\n"
		<< html;

	return ss.str();
}
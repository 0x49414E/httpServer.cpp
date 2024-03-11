#ifndef SERVER
#define SERVER

#include "Sock.h"

class Server : public Sock
{
private:
	SOCKET clientSock;
	int addrlen;
	std::string response;
public:
	Server(const char* host, unsigned short port);
	~Server();

	bool BindSocket();
	bool Listen(int backlog);
	virtual void Connect() override;
	void HandleRequest(const char* request, SOCKET& clientSock);
	void GenerateResponse(unsigned short status_code = 200);
};

#endif
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
	std::string GenerateResponse();
};

#endif
#include "Server.h"

constexpr auto HOST = "0.0.0.0";
constexpr auto PORT = 8000;

int main()
{
	Server server{ HOST, PORT };
	
	if (!server.DLLInitialization() 
		|| !server.CreateSocket()
		|| !server.BindSocket()
		|| !server.Listen(10))
	{
		return 1;
	}

	server.Connect(); 

	return 0;
}
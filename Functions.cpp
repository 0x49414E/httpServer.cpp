#include "Functions.h"

std::vector<std::string> parse(const char* _request)
{
	std::istringstream request(_request);

	std::string method, uri, protocol;

	if (std::getline(request, method, ' ') 
		&& std::getline(request, uri, ' ') 
		&& std::getline(request, protocol))
	{
		return { method,uri,protocol };
	}
	else
	{
		return { "Error parsing the request" };
	}
}
#include "pch.h"
#include "TypeSocket.h"


class TCPNetworkManager
{
    public:
	TCPNetworkManager( void ) noexcept;
	~TCPNetworkManager( void ) noexcept;

	bool open( void ) noexcept;
	
	bool setAddress( char* hostName, char* sname, char* protocol ) noexcept;
	bool isValid( void ) const noexcept;

    private:
	SOCKET _socket;
	sockaddr_in _local;
	sockaddr_in _peer;

};

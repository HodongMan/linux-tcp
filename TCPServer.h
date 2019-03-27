#include "pch.h"
#include "TypeSocket.h"


class TCPNetworkManager
{
    public:
	TCPNetworkManager( void ) noexcept;
	~TCPNetworkManager( void ) noexcept;

	bool open( void ) noexcept;
	
	bool setAddress( const char* hostName, const char* sname, const char* protocol ) noexcept;
	bool isValid( void ) const noexcept;

	void run( void ) noexcept;

	void connect( SOCKET s, struct sockaddr_in* peer ) noexcept;

    private:
	SOCKET _socket;
	sockaddr_in _local;
	sockaddr_in _peer;

};

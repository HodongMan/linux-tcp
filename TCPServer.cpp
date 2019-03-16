#include "TCPServer.h"

TCPNetworkManager::TCPNetworkManager( void ) noexcept
{
    _socket = 0;
}

TCPNetworkManager::~TCPNetworkManager( void ) noexcept
{

}

bool TCPNetworkManager::open( void ) noexcept
{
    _socket = socket( AF_INET, SOCK_STREAM, 0 );

    if ( false == isValid() )
    {
	printf("Socket Error");
    }

    return true;
}

bool TCPNetworkManager::setAddress( char* hostName, char* sname, char* protocol ) noexcept
{
    short port;
    struct hostent* hp;

    bzero( _local, sizeof(*_local) );
    
    _local->sin_family = AF_INET;

    if ( nullptr != hostName )
    {
	if ( !inet_aton( hostName, &_local->sin_addr ) )
	{
	    hp = gethostbyname( hostName );
	    if ( nullptr == hp )
	    {
		printf( "invalid host %s\n", )
	    }
	}
    }
}

bool TCPNetworkManager::isValid( void ) const noexcept
{
    return _socket >= 0;
}

#include "TCPServer.h"

TCPNetworkManager::TCPNetworkManager( void ) noexcept
{
    _socket 	= 0;
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

bool TCPNetworkManager::setAddress( const char* hostName, const char* sname, const char* protocol ) noexcept
{
    short port;
    struct servent* sp;
    struct hostent* hp;
    char* endptr;

    bzero( &_local, sizeof( _local ) );
    
    _local.sin_family = AF_INET;
    
    if ( nullptr != hostName )
    {
	if ( !inet_aton( hostName, &_local.sin_addr ) )
	{
	    hp = gethostbyname( hostName );
	    if ( nullptr == hp )
	    {
		printf( "invalid host %s\n", hostName );
		
		return false;
	    }

	    _local.sin_addr = *(struct in_addr*)hp->h_addr;
	}
    }
    else
    {
	_local.sin_addr.s_addr = htonl( INADDR_ANY );
    }

    port = strtol( sname, &endptr, 0);

    if ( '\0' == *endptr)
    {
	_local.sin_port = htons( port );
    }
    else
    {
	sp = getservbyname( sname, protocol );
	if ( nullptr == sp)
	{
	    printf( "unknown service : %s\n", sname );

	    return false;
	}

	_local.sin_port = sp->s_port;

    }

    return true;
}

bool TCPNetworkManager::isValid( void ) const noexcept
{
    return _socket >= 0;
}

void TCPNetworkManager::run( void ) noexcept
{

    int peerlen		 	= 0;
    const int on 		= 1;
    struct sockaddr_in peer;
    SOCKET s1;

    if ( false == isValid() )
    {
	return;
    }

    if ( setsockopt( _socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof( on ) ) )
    {
	printf("setsockopt error");
	return;
    }

    if ( bind( _socket, (struct sockaddr*)&_local, sizeof( _local ) ) )
    {
	printf("bind error");
	return;
    }

    if ( listen( _socket, 5 ) )
    {
	printf("listen error");
	return;
    }

    while( true )
    {
	peerlen = sizeof( peer );
	s1 = accept( _socket, (struct sockaddr*)&peer, (socklen_t*)&peerlen );
	connect( s1, &peer );
    }
}

void TCPNetworkManager::connect( SOCKET s, struct sockaddr_in* peer ) noexcept
{
    send( s, "Hello World!\n", 13, 0);
}

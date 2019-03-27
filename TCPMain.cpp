#include "TCPServer.h"

int main( int argc, char** argv )
{
    TCPNetworkManager manager = TCPNetworkManager();

    manager.open();
    manager.setAddress( "localhost", "9000", "tcp" );
    manager.run();

    return 0;
}

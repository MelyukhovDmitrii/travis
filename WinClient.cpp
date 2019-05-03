#include <stdio.h>
#include "winsock2.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	char *host;
	int port;

	if (argc < 3) {
		return 1;
	} else {
		host = argv[1];
		port = atoi(argv[2]);
	}

    // Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
        printf("Error at WSAStartup()\n");

    // Create a socket.
    SOCKET m_socket;
    m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if ( m_socket == INVALID_SOCKET )
    {
        printf( "Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }

    // Connect to a server.
    struct sockaddr_in clientService;

    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( host );
    clientService.sin_port = htons(port);

    if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR)
    {
        printf( "Failed to connect.\n" );
        WSACleanup();
        return 1;
    }

	string buff;

    while(1)
    {
		buff = "";
		buff.resize(1024);
		int n = recv(m_socket, (char *) buff.c_str(), 1024, 0);
		string subs = buff.substr(0, n);
		if (subs.compare("check") == 0) {
			send(m_socket, buff.c_str(), n, 0);
		}
		else {
			if (n > 0) {
				cout << buff.c_str() << endl;
			}
		}
    }
    return 0;
}

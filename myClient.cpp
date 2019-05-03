#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <stdio.h>
#include <zconf.h>
#include <iostream>
#include <cstring>

using namespace std;

string buff;
char buffer[1024];

int main()
{

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    while (1){
        buff = "";
        buff.resize(1024);
        int n = recv(sock, (void *) buff.c_str(), 20, 0);
        string subs = buff.substr(0, n);
        if(buff.substr(0, n).compare("check") == 0){
            send(sock, buff.c_str(), n, 0);
        } else {
            if(n > 0){
                cout << buff << endl;
            }
        }
    }

    return 0;
}

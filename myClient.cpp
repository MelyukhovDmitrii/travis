#include "myClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <stdio.h>
#include <zconf.h>
#include <iostream>
#include <cstring>

using namespace std;

std::string getOneResponse(){
    string buff;
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

    buff = "";
    buff.resize(1024);
    int n = recv(sock, (void *) buff.c_str(), 1024, 0);
    string subs = buff.substr(0, n);
    if(buff.substr(0, n).compare("check") == 0){
        send(sock, buff.c_str(), n, 0);
    } else {
        if(n > 0){
            close(sock);
            return buff;
        }
        if(n == 0){
            perror("close");
            close(sock);
            return "";
        }
    }
}

int init(int count){
    string buff;
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
    sleep(1);
    while (count != 0){
        count--;
        buff = "";
        buff.resize(1024);
        int n = recv(sock, (void *) buff.c_str(), 1024, 0);
        string subs = buff.substr(0, n);
        if(buff.substr(0, n).compare("check") == 0){
            send(sock, buff.c_str(), n, 0);
        } else {
            if(n > 0){
                cout << buff;
            }
            if(n == 0){
                perror("close");
                close(sock);
                return 1;
            }
        }
    }
    close(sock);
    return 0;
}

#include "myServer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <stdio.h>
#include <zconf.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

struct Socket {
    Socket(int socket, sockaddr_in addr){
        this->addr = addr;
        this->socket = socket;
    }
    int socket;
    sockaddr_in addr;
};

vector<Socket> clients;

Socket socketAccept(int listener){
    sockaddr_in addr;
    unsigned int size = sizeof(addr);
    int socks = accept(listener, (sockaddr*)&addr, &size);
    Socket socket(socks, addr);
    return socket;
}

bool checkSocketResponse(Socket socket){
    string mes = "check";
    int n  = send(socket.socket, mes.c_str(), mes.length(), 0);
    mes = "";
    mes.resize(n);
    int n2 = recv(socket.socket, (void *) mes.c_str(), n, 0);
    string subs = mes.substr(0, n2);
    if(subs.compare("check") == 0){
        return true;
    } else {
        return false;
    }
}

void sendMessageToAllSockets(vector<Socket> *cs, string m){
    for(int i = 0; i < cs->size(); i++){
        send(cs->at(i).socket, m.c_str(), m.length(), 0);
    }
}

void checkAllSocketsResponse(vector<Socket> *cs, Socket socket){
    for(int i = 0; i < cs->size(); i++){
        if(!checkSocketResponse(cs->at(i))){
            char *ip = inet_ntoa(cs->at(i).addr.sin_addr);
            string s = "DOWN ";
            s.append(ip);
            s.append("\n");
            cs->erase(cs->begin() + i);
            checkAllSocketsResponse(cs, socket);
            sendMessageToAllSockets(cs, s);
            send(socket.socket, s.c_str(), s.length(), 0);
            break;
        }
    }
}

void sendIpOfAllSocketsToSocket(vector<Socket> *cs, Socket socket){
    for(int i = 0; i < cs->size(); i++){
        char *ip = inet_ntoa(cs->at(i).addr.sin_addr);
        string s = "UP ";
        s.append(ip);
        s.append("\n");
        send(socket.socket, s.c_str(), s.length(), 0);
    }
}

void sendSocketIpToAllSockets(vector<Socket> *cs, Socket socket){
    for(int i = 0; i < cs->size(); i++){
        char *ip = inet_ntoa(socket.addr.sin_addr);
        string s = "UP ";
        s.append(ip);
        s.append("\n");
        send(cs->at(i).socket, s.c_str(), s.length(), 0);
    }
}

int initServer()
{
    int listener;
    struct sockaddr_in addr;

    string buf;
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
    }

    listen(listener, 1);

    while(1) {
        Socket socket = socketAccept(listener);
        //cout << inet_ntoa(socket.addr.sin_addr) << endl;
        string hello = "hello";
        hello.append("\n");
        send(socket.socket, hello.c_str(), hello.length(), 0);
        if(socket.socket < 0) {
            close(socket.socket);
        } else {
            checkAllSocketsResponse(&clients, socket);
            sendIpOfAllSocketsToSocket(&clients, socket);
            sendSocketIpToAllSockets(&clients, socket);
            clients.push_back(socket);
        }
    }
    return 0;
}

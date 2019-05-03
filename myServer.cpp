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

Socket* socketAccept(int listener){
    sockaddr_in addr;
    unsigned int size = sizeof(addr);
    int socks = accept(listener, (sockaddr*)&addr, &size);
    Socket* socket = new Socket(socks, addr);
    return socket;
}

bool checkSocketResponse(Socket *socket){
    string mes = "check";
    int n  = send(socket->socket, mes.c_str(), mes.length(), 0);
    mes = "";
    mes.resize(100);
    int n2 = recv(socket->socket, (void *) mes.c_str(), 1024, 0);
    string subs = mes.substr(0, n2);
    if(subs.compare("check") == 0){
        return true;
    } else {
        return false;
    }
}

void sendMessageToAllSockets(vector<Socket> *clients, string message){
    for(int i = 0; i < clients->size(); i++){
        send(clients->at(i).socket, message.c_str(), message.length(), 0);
    }
}

void checkAllSocketsResponse(vector<Socket> *clients){
    for(int i = 0; i < clients->size(); i++){
        if(!checkSocketResponse(&clients->at(i))){
            char *ip = inet_ntoa(clients->at(i).addr.sin_addr);
            string s = "DOWN ";
            s.append(ip);
            clients->erase(clients->begin() + i);
            checkAllSocketsResponse(clients);
            sendMessageToAllSockets(clients, s);
            break;
        }
    }
}

void sendIpOfAllSocketsToSocket(vector<Socket> *clients, Socket *socket){
    for(int i = 0; i < clients->size(); i++){
        char *ip = inet_ntoa(clients->at(i).addr.sin_addr);
        string s = "UP ";
        s.append(ip);
        send(socket->socket, s.c_str(), s.length(), 0);
    }
}

void sendSocketIpToAllSockets(vector<Socket> *clients, Socket *socket){
    for(int i = 0; i < clients->size(); i++){
        char *ip = inet_ntoa(socket->addr.sin_addr);
        string s = "UP ";
        s.append(ip);
        send(clients->at(i).socket, s.c_str(), s.length(), 0);
    }
}

int main()
{
    int sock, listener;
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
        Socket* socket = socketAccept(listener);
        cout << inet_ntoa(socket->addr.sin_addr) << endl;
        if(socket->socket < 0) {
            perror("accept");
            close(socket->socket);
        } else {
            checkAllSocketsResponse(&clients);
            sendIpOfAllSocketsToSocket(&clients, socket);
            sendSocketIpToAllSockets(&clients, socket);
            clients.push_back(*socket);
        }


        /*while(1)
        {

            bool b =  checkSocketResponse(socket);
            if(b) {
                cout << "true";
            };
            bytes_read = recv(socket->socket, (void *) buf.c_str(), 1024, 0);
            if(bytes_read <= 0) break;
            printf(buf.c_str());
            int i = send(socket->socket, buf.c_str(), bytes_read, MSG_NOSIGNAL);
            cout << i << endl;
            send(socket->socket, buf.c_str(), bytes_read, 0);
        }*/
    
        //close(socket->socket);
    }
    
    return 0;
}

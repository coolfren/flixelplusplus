#include "flixel++/FlxNet.hpp"

Flx::Net::Net(const char* host, int port) {
    #ifdef _WIN32
    #else
    sock = socket(AF_INET, SOCK_STREAM, 0);
    hostent* hostentity = gethostbyname(host);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr, hostentity->h_addr_list[0], hostentity->h_length);
    #endif
}

Flx::Net::~Net() {
    
}

void Flx::Net::listen(int connections) {
    #ifdef _WIN32
    #else
    ::listen(sock, connections);
    #endif
}

void Flx::Net::send(const char* data) {
    #ifdef _WIN32
    #else
    ::send(sock, data, strlen(data), 0);
    #endif
}

void Flx::Net::connect() {
    #ifdef _WIN32
    #else
    ::connect(sock, (sockaddr*)&addr, sizeof(addr));
    #endif
}
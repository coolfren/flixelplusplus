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
    shutdown(sock, 2);
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

std::string Flx::Net::read() {
    #ifdef _WIN32
    #else
    std::string str;
    int recvsize = 0;
    char buffer[1024];
    while((recvsize = ::recv(sock, buffer, 1024, 0)) > 1)
    {
        std::cout << recvsize << std::endl;
        str.append(buffer, recvsize);
    }
    return str;
    #endif
}

std::string Flx::Net::readUntil(char until) {
    #ifdef _WIN32
    #else
    std::stringbuf buffer;
    while(true)
    {
        char c;
        ssize_t code = ::recv(sock, &c, 1, 0);
        if(c == until || code < 1)
            break;
        buffer.sputc(c);
    }
    return buffer.str();
    #endif
}

void Flx::Net::connect() {
    #ifdef _WIN32
    #else
    ::connect(sock, (sockaddr*)&addr, sizeof(addr));
    #endif
}
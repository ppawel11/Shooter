//
// Created by pawel on 29.04.2020.
//

#include "TcpConnection.h"

TcpConnection::TcpConnection(){
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server::ip);
    server_address.sin_port = htons(server::tcp_port);
}

void TcpConnection::initSocket(){
    if((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::runtime_error("socket call error");

}

void TcpConnection::connectToServer() {
    if (connect(sockfd, (struct sockaddr *) &server_address, sizeof (server_address)) != 0)
        throw std::runtime_error("connect call error");
}

void TcpConnection::sendPacket(const char *buf, int len) {
    for(int total_sent = 0, now_sent = 0; total_sent < len; total_sent += now_sent) {
        now_sent = send(sockfd, &buf+total_sent, len - total_sent, MSG_NOSIGNAL);
        if(now_sent < 0)
            throw std::runtime_error("sending problem");
    }
}

std::string TcpConnection::readPacket() {
    std::lock_guard<std::mutex> guard(mutex_send_recv);
    char buf[protocol::max_size] = {0};
    int received = recv(sockfd, &buf, sizeof(buf),  MSG_DONTWAIT);
    if(received > 0)
        return std::string(buf, buf+received);
    return std::string(buf);
}

//
// Created by pawel on 29.04.2020.
//

#include "UdpConnection.h"

UdpConnection::UdpConnection() {
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server::ip);
    server_address.sin_port = htons(server::udp_port);

    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(client::ip);
    client_address.sin_port = htons(client::port);

}

void UdpConnection::initSocket() {
    if((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
        throw "socket call error";
    if(bind (sockfd, (struct sockaddr *) &client_address, sizeof (client_address)) < 0)
        throw "bind error";
}

void UdpConnection::sendPacket(const char *buf) {
    int packet_size = strlen(buf);
    std::cout<<"UDP SEND : "<<buf<<std::endl;
    for(int total_sent = 0, now_sent = 0; total_sent < packet_size; total_sent += now_sent) {
        now_sent = sendto(sockfd, buf + total_sent, packet_size - total_sent, MSG_NOSIGNAL, (const struct sockaddr *) &server_address, sizeof(server_address));
        if(now_sent < 0)
            throw "sending problem";
    }
}

std::string UdpConnection::readPacket() {
    char buf[protocol::max_size] = {0};
    socklen_t server_address_length = sizeof(server_address);
    int received = recvfrom(sockfd, &buf, protocol::max_size, MSG_DONTWAIT, (struct sockaddr *) &server_address, &server_address_length );
    if(received <= 0)
        return "";
    return std::string(buf);
}

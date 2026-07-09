#include "sockets.h"

int main(void)
{
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // create socket
    if (socket_fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in proxy_addr;

    // initialise sock address:
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_port = htons(7777);
    if (inet_pton(AF_INET, "127.0.0.1", &(proxy_addr.sin_addr)) != 1)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // bind socket to address
    if (bind(socket_fd, (struct sockaddr *)(&proxy_addr), sizeof(proxy_addr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // now we are ready to receive UDP datagrams on on 127.0.0.1:7777

    // initialise vars for receiving:
    char rec_buff[100];
    size_t max_len = 90;
    struct sockaddr_in rec_addr;
    socklen_t rec_addr_size = sizeof(rec_addr); // we're telling the kernel how much space is available in rec_addr

    // initialise variables for sending:
    char send_buff[100];
    struct sockaddr_in send_addr;
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(4242);
    if (inet_pton(AF_INET, "127.0.0.1", &(send_addr.sin_addr)) != 1)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        // first we receive request from udp_cient:
        ssize_t rec = recvfrom(socket_fd, rec_buff, max_len, 0, (struct sockaddr *)(&rec_addr), &rec_addr_size);
        // the kernel tells us how much data it wrote into rec_addr from the (newly modified) rec_addr_size.
        if (rec < 0)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);       
        }
        rec_buff[rec] = '\0';

        
        // next we send to udp_server:
        ssize_t send = sendto(socket_fd, rec_buff, rec, 0, (struct sockaddr *)(&send_addr), sizeof(send_addr));
        if (send < 0)
        {
            perror("sendto");
            exit(EXIT_FAILURE);       
        }

        // then we receive the reply from the udp_server
        ssize_t rec2 = recvfrom(socket_fd, send_buff, max_len, 0, NULL, NULL);
		// the struct sockaddr * is set to NULL meaning we don't record info about who sent the message in any struct
		// second NULL because the struct has no size (since we have no struct)
        if (rec2 < 0)
        {
            perror("recvfrom2");
            exit(EXIT_FAILURE);       
        }
        send_buff[rec2] = '\0';

        // lastly we send the reply we got from udp_server to udp_client
        ssize_t send2 = sendto(socket_fd, send_buff, rec2, 0, (struct sockaddr *)(&rec_addr), rec_addr_size);
        // char ip_addr[16];
        // inet_ntop(AF_INET, , )
        // printf("IP address = %s", ip_addr);
        if (send2 < 0)
        {
            perror("sendto2");
            exit(EXIT_FAILURE);       
        }
    }
    close(socket_fd);
}
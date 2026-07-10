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
    char rec_buff[4096]; // classic DNS over UDP normally fits into 512 bytes but modern DNS can use larger messages
    size_t max_len = 4096;
    struct sockaddr_in rec_addr;
    socklen_t rec_addr_size; // we're telling the kernel how much space is available in rec_addr
    // initialise variables for sending:
    char send_buff[4096];
    struct sockaddr_in send_addr;
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(53);
    if (inet_pton(AF_INET, "127.0.0.53", &(send_addr.sin_addr)) != 1)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        rec_addr_size = sizeof(rec_addr); // we're telling the kernel how much space is available in rec_addr

        // first we receive request from udp_cient:
        ssize_t rec = recvfrom(socket_fd, rec_buff, max_len, 0, (struct sockaddr *)(&rec_addr), &rec_addr_size);
        // the kernel tells us how much data it wrote into rec_addr from the (newly modified) rec_addr_size.
        if (rec < 0)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);       
        }
        //rec_buff[rec] = '\0'; null termination is no longer needed - as DNS is binary, not strings 

        ssize_t rec_2;
        if (is_secret_domain(&(rec_buff[12]))) // if we query for dima.com, return hardcoded records
        {
            rec_2 = load_response(send_buff, rec_buff, rec);
        }
        else 
        {
            // next we send to dns_resolver:
            ssize_t send = sendto(socket_fd, rec_buff, rec, 0, (struct sockaddr *)(&send_addr), sizeof(send_addr));
            if (send < 0)
            {
                perror("sendto");
                exit(EXIT_FAILURE);       
            }

            // then we receive the reply from the dns_resolver
            rec_2 = recvfrom(socket_fd, send_buff, max_len, 0, NULL, NULL);
            // the struct sockaddr * is set to NULL meaning we don't record info about who sent the message in any struct
            // second NULL because the struct has no size (since we have no struct)
            if (rec_2 < 0)
            {
                perror("recvfrom2");
                exit(EXIT_FAILURE);       
            }
            //send_buff[rec2] = '\0';            
        }


        // lastly we send the reply we got from udp_server to udp_client
        ssize_t send2 = sendto(socket_fd, send_buff, rec_2, 0, (struct sockaddr *)(&rec_addr), rec_addr_size);
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
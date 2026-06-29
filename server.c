#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4242);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("Waiting for client...\n");

    int client_fd = accept(server_fd, NULL, NULL);

    printf("Client connected.\n");

    char buffer[100];

    while (1)
    {
        int n = read(client_fd, buffer, 99);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        printf("Server received: %s", buffer);

        write(client_fd, "message received\n", 17);
    }

    printf("Client disconnected.\n");

    close(client_fd);
    close(server_fd);
}
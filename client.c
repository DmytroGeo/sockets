#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4242);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    printf("Connected to server.\n");
    printf("Type messages. Press Ctrl-D to quit.\n");

    char message[100];
    char reply[100];

    while (fgets(message, 100, stdin) != NULL)
    {
        write(fd, message, strlen(message));

        int n = read(fd, reply, 99);

        if (n <= 0)
            break;

        reply[n] = '\0';

        printf("Server replied: %s", reply);
    }

    close(fd);
}
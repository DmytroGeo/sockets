#include "sockets.h"

int	main(void)
{
	int	socket_fd;

	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

	// bind() should only be used for server - it gives the socket a local address/port that the OS can deliver received datagrams to.
	// using bind in both server and client will result in one process saying "address already in use".
	// the OS gives the client some ephemeral port.

	// note: It may seem that socket_fd is the same for client and server (3 for both) but (see 'man socket'):
	// 'The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.'
	// meaning file descriptors are not global, they are per-process, so these socket_fds are different 3s.

    // printf("The client thinks the socket 1 is %d\n", socket_fd);

	//sleep(30);

	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(7777);
	if (inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr)) != 1)
	{
		perror("inet_pton");
		exit(EXIT_FAILURE);
	}

	ssize_t sent;
	ssize_t received;
	int max_input_len = 90;
	char send_buff[100];
	char rec_buff[100];

	while (fgets(send_buff, max_input_len, stdin))
	{
		sent = sendto(socket_fd, send_buff, ft_strlen(send_buff), 0, (struct sockaddr *)&addr, sizeof(addr));
		if (sent < 0)
		{
			perror("sendto");
			exit(EXIT_FAILURE);
		}
		received = recvfrom(socket_fd, rec_buff, max_input_len, 0, NULL, NULL);
		if (received < 0)
		{
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		rec_buff[received] = '\0';
		printf("We received this reply from the server: %s", rec_buff);
	}
	close(socket_fd);
}
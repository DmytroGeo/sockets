#include "sockets.h"

int	main(void)
{
	int	socket_fd;

	// domain: AF_INET - use IPv4
	// type: SOCK_DGRAM - use datagrams (does not imply UDP - UDP-lite exists apparently)
	// protocol: 0 - pick the default transport protocol (in this case UDP)
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("The client thinks the socket is %d\n", socket_fd);
}
#include "sockets.h"

int	main(void)
{
	int	socket_fd;

	// domain: AF_INET - use IPv4
	// type: SOCK_DGRAM - use datagrams (does not imply UDP - UDP-lite exists apparently)
	// protocol: 0 - pick the default transport protocol (in this case UDP)

	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd < 0)
		return(perror("socket creation error"), EXIT_FAILURE);

    //printf("The server thinks the socket is %d\n", socket_fd);
	//after the above command, a socket exists but doesn not have an address yet (we want it to bind to 127.0.0.1:4242).
	//This is where we need the 'bind()' function.
	// looking at the man page for the bind function we see it's prototype is 
	// int bind(int sock_fd, const struct sockaddr *addr, socklen_t addrlen);
	// We have our sock_fd from above but NOT a const struct sockaddr *addr.

// Internet domain sockets
//        #include <netinet/in.h>

//        struct sockaddr_in {
//            sa_family_t     sin_family;     /* AF_INET */
//            in_port_t       sin_port;       /* Port number */
//            struct in_addr  sin_addr;       /* IPv4 address */
//        };
}
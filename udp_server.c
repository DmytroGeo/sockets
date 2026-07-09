#include "sockets.h"

// NOT USED:

// int not_in_range(int n)
// {
// 	if (n < 0 || n > 255)
// 		return 1;
// 	return 0;
// }
// size_t	power(int raise, int raise_to)
// {
// 	if (raise < 0 || raise_to < 0)
// 		exit(EXIT_FAILURE);
// 	if (raise_to == 0)
// 		return (1);
// 	return(raise * power(raise, raise_to - 1));
// }

// size_t convert_ip(int octet_1, int octet_2, int octet_3, int octet_4)
// {
// 	size_t	converted;

// 	if (not_in_range(octet_1) || not_in_range(octet_2) || not_in_range(octet_3) || not_in_range(octet_4))
// 		exit(EXIT_FAILURE);
// 	converted = octet_1 * power(256, 3) + octet_2 * power(256, 2) + octet_3 * power(256, 1) + octet_4 * power(256, 0);
// 	return (converted);
	
// }

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

	// for IPv4 the struct we want is sockaddr_in:
	//        #include <netinet/in.h>

	//        struct sockaddr_in {
	//            sa_family_t     sin_family;     /* AF_INET */
	//            in_port_t       sin_port;       /* Port number */
	//            struct in_addr  sin_addr;       /* IPv4 address */
	//        };
	struct sockaddr_in addr;

	addr.sin_family = AF_INET; // prediction - fine as is 
	//addr.sin_port = 4242; // prediction - fine as is
	//addr.sin_addr.s_addr = convert_ip(127, 0, 0, 1); // prediction - needs conversion
	//printf("The port is %u\n", addr.sin_port);
	// printf("The IPv4 addr is %u\n", addr.sin_addr.s_addr);
	// so actually, only AF_INET doesn't need conversion.
	// Both port and ip do need conversion, but they have their own conversion functions. Why?
	// because (see man 7 ip) the port and ip must be in 'network byte order'.
	// From 'man 7 ip': 'In particular, this means that you need to call htons(3) on the  number  that  is  as‐signed to a port.'
	addr.sin_port = htons(4242); //htons = (h)ost (to) (n)etwork (s)hort
	// and we must use inet_ptons to convert IPv4 and IPv6 addresses from text to binary form (requires <arpa/inet.h>)
	// from 'man inet_pton': The address is converted to a struct in_addr and copied to dst, which must be sizeof(struct in_addr) (4) bytes (32bits) long.'
	// so we first declare the buffer we want to copy into:
	struct in_addr buffer;
	// then do conversion and copying:
	int check = inet_pton(AF_INET, "127.0.0.1", &buffer);
	if (check != 1)
	{
		perror("inet_pton");
		exit(EXIT_FAILURE);
	}
	addr.sin_addr = buffer;
	// now that we've set up the sockaddr (127.0.0.1:4242) correctly it's time to bind our socket to the address with the bind function:
	// bind accepts struct sockaddr * but that's just a generic socket address type. So we cast it like so:
	bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
	// Now our socket is atached to address 127.0.0.1:4242
	// to test this we set a sleep() at the end of our programme and, while it's running
	// in another terminal we scan for open oprts with ss (used to dump socket statistics).
	// exact command is 'ss -lunp | grep 4242'
	// sleep(30);
}
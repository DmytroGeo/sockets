#include "sockets.h"

size_t ft_strlen(const char *str)
{
    size_t len = 0;
    if (!str)
        return (len);
    while (str[len])
        len++;
    return (len);
}

int is_secret_domain(char *domain)
{
    return (domain[0] == 4 &&
        domain[1] == 'd' &&
        domain[2] == 'i' &&
        domain[3] == 'm' &&
        domain[4] == 'a' &&
        domain[5] == 3 &&
        domain[6] == 'c' &&
        domain[7] == 'o' &&
        domain[8] == 'm' &&
        domain[9] == 0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	// Arguments: void *dest – pointer to the destination memory block, const void *src – pointer to the source memory block, size_t n – number of bytes to copy.
	// Returns: A pointer to the destination memory block 'dest'.
	// This function copies the first 'n' bytes from the source memory block 'src' to the destination memory block 'dest', and returns the destination pointer.
	unsigned char		*d;
	unsigned const char	*s;

	d = dest;
	s = src;
	while (n != 0)
	{
		n--;
		d[n] = s[n];
	}
	return (dest);
}

ssize_t load_response(char send_buff[], char rec_buff[], ssize_t rec)
{
    int answer_offset;

    // copy original query
    ft_memcpy(send_buff, rec_buff, rec);

    // set response bit
    send_buff[2] |= 0x80;

    // set answer count to 1
    send_buff[6] = 0x00;
    send_buff[7] = 0x01;

    // question ends at rec
    answer_offset = rec;

    unsigned char answer[] = {
        0xc0, 0x0c,       // pointer to dima.com
        0x00, 0x01,       // type A
        0x00, 0x01,       // class IN
        0x00, 0x00, 0x70, 0x80, // TTL
        0x00, 0x04,       // IPv4 length
        0x11, 0x04, 0x11, 0x04
    };

    ft_memcpy(&send_buff[answer_offset], answer, sizeof(answer));

    return answer_offset + sizeof(answer);
}
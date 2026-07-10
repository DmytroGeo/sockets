#ifndef SOCKETS_H
# define SOCKETS_H

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

size_t ft_strlen(const char *str);
int is_secret_domain(char *domain);
ssize_t load_response(char send_buff[], char rec_buff[], ssize_t rec);

#endif

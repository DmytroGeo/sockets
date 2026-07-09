COMP= cc -Wall -Wextra -Werror -g3
CLI=udp_client
SRV=udp_server
PROXY=udp_proxy
UTIL=utils.c
RM = rm -f

all: $(CLI) $(SRV) $(PROXY)

$(SRV): $(SRV).c
	$(COMP) $(SRV).c $(UTIL) -o $(SRV)

$(CLI): $(CLI).c
	$(COMP) $(CLI).c $(UTIL) -o $(CLI)

$(PROXY): $(PROXY).c
	$(COMP) $(PROXY).c $(UTIL) -o $(PROXY)

clean fclean:
	$(RM) $(CLI) $(SRV) $(PROXY)

re: clean all

COMP= cc -Wall -Wextra -Werror -g3
CLI=udp_client
SRV=udp_server
PROXY=udp_proxy
DNS=dns_proxy
UTIL=utils.c
RM = rm -f
ALL=$(CLI) $(SRV) $(PROXY) $(DNS)
all: $(ALL)

$(SRV): $(SRV).c
	$(COMP) $(SRV).c $(UTIL) -o $(SRV)

$(CLI): $(CLI).c
	$(COMP) $(CLI).c $(UTIL) -o $(CLI)

$(DNS): $(DNS).c
	$(COMP) $(DNS).c $(UTIL) -o $(DNS)

$(PROXY): $(PROXY).c
	$(COMP) $(PROXY).c $(UTIL) -o $(PROXY)

clean fclean:
	$(RM) $(ALL)

re: clean all

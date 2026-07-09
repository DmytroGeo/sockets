COMP= cc -Wall -Wextra -Werror -g3
CLI=udp_client
SRV=udp_server
UTIL=utils.c
RM = rm -f

all: $(CLI) $(SRV)

$(SRV): $(SRV).c
	$(COMP) $(SRV).c $(UTIL) -o $(SRV)

$(CLI): $(CLI).c
	$(COMP) $(CLI).c $(UTIL) -o $(CLI)

clean:
	$(RM) $(CLI) $(SRV)

re: clean all

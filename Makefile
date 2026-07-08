COMP= cc -Wall -Wextra -Werror
CLI=udp_client
SRV=udp_server
RM = rm -f

all: $(CLI) $(SRV)

$(SRV):
	$(COMP) $(SRV).c -o $(SRV)

$(CLI):
	$(COMP) $(CLI).c -o $(CLI)

clean:
	$(RM) $(CLI) $(SRV)

re: clean all

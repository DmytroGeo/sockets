
all:
	cc server.c -o server
	cc client.c -o client

clean:
	rm -f client
	rm -f server

re: clean all

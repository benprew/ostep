all: server

clean:
	rm -f server

server: http_server.c
	gcc -Wall -O http_server.c -o server

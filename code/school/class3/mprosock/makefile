
.PHONY:all
all:tcp_client tcp_server
tcp_client:tcp_client.c
	gcc -o tcp_client tcp_client.c
tcp_server:tcp_server.c
	gcc -o tcp_server tcp_server.c
.PHONY:clean
clean:
	rm -f tcp_client tcp_server

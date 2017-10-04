.PHONY:all
all::client server

client:client.c comn.c
	gcc -o $@ $^
server:server.c comn.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f client server

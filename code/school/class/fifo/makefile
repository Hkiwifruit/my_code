.PHONY:all
all:serve client

serve:serve.c
	gcc -o $@ $^
client:client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f serve client mypipe

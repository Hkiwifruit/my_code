ROOT=$(shell pwd)
LDFLAGS=-lpthread
cc=gcc
bin=httpd
src=$(shell ls *.c)

$(bin):$(src)
	$(cc) -o $@ $^ $(LDFLAGS)
.PHONY:clean
clean:
	rm -f $(bin)
.PHONY:debug
debug:
	@echo $(src)

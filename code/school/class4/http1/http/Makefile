ROOT_PATH=$(shell pwd)
CONF=$(ROOT_PATH)/conf
PLUGIN=$(ROOT_PATH)/plugin
WWWROOT=$(ROOT_PATH)/wwwroot
CGI_BIN=$(WWWROOT)/cgi-bin
SQL=$(ROOT_PATH)/sql_connect
FLAGS=-D_STDOUT_
LDFLAGS=-lpthread

cc=gcc
bin=httpd
src=httpd.c main.c
obj=$(shell echo $(src) | sed 's/\.c/\.o/g')

.PHONY:all
all:$(bin) cgi
$(bin):$(obj)
	$(cc) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(cc) -c $< $(FLAGS)
cgi:
	cd $(WWWROOT)/cgi-bin;make;cp math_cgi $(ROOT_PATH);cd - 
	cd $(SQL);make;mv insert_cgi $(ROOT_PATH);mv select_cgi $(ROOT_PATH);cd -

.PHONY:clean
clean:
	rm -f *.o $(bin);cd $(WWWROOT)/cgi-bin;make clean;cd -
	cd $(SQL);make clean;cd -;rm -f insert_cgi select_cgi math_cgi calcDAD calcDSD
	rm -r output
.PHONY:debug
debug:
	@echo $(src)

.PHONY:output
output:
	mkdir -p output/wwwroot/cgi-bin
	mkdir -p output/conf
	cp conf/server.conf output/conf
	cp httpd output
	cp math_cgi output/wwwroot/cgi-bin
	cp insert_cgi output/wwwroot/cgi-bin
	cp select_cgi output/wwwroot/cgi-bin
	cp $(CGI_BIN)/calcDAD output/wwwroot/cgi-bin
	cp $(CGI_BIN)/calcDSD output/wwwroot/cgi-bin
	cp wwwroot/index.html output/wwwroot
	cp $(PLUGIN)/ctl_server.sh output

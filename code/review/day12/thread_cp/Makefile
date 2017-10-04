.PHONY:clean

TARGET=mian
OBJECT=main.o threadpool.o condition.o

CC=gcc
FLAGS=-pthread -lrt -Wall

$(TARGET):$(OBJECT)
	$(CC) -o $@ $^ $(FLAGS)

%.o:%.c
	$(CC) -c $< 

clean:
	rm -f $(TARGET) $(OBJECT)

.PHONY:clean

TARGET=main
OBJCTS=condition.o threadpool.o main.o

CC=gcc
FLAGS=-lpthread -Wall

all:$(TARGET)

$(TARGET):$(OBJECT)
	$(CC) $^ -o $@ $(FLAGS)

%.o:%.c
	$(CC) -c $^ -o $@

clean:
	rm -rf $(OBJECT) $(TARGET)

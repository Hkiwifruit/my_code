.PHONY : create erase clean

TARGET= create \
				erase
CC=gcc

all: $(TARGET)

create :01.c
		$(CC) $^ -o $@
erase :02.c
		$(CC) $^ -o $@

clean:
		rm  $(TARGET)

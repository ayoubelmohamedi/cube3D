CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = myprogram
SRCS = $(wildcard *.c) $(wildcard ./../../get_next_line/*.c) 
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run all
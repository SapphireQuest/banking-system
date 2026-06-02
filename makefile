CC = gcc -fsanitize=undefined
CFLAGS = -g -Wall -pedantic

TARGET = banking_system

SRCS = main.c bank.c database.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
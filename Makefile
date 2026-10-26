CC      = gcc
CFLAGS  = -Wall -Werror -std=c99 -fstack-protector -I.
TARGET  = ProjetC

SRC = main.c utils.c colors.c $(wildcard formes/*.c)
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean $(TARGET)

.PHONY: clean re
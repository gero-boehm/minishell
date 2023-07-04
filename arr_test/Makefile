CC=cc
CFLAGS=
NAME=array
SRC=main.c array.c vars.c
OBJ=$(SRC:.c=.o)
HEADERS=array.h

ifndef LENIENT
	CFLAGS += -Wall -Wextra -Werror
endif

ifdef DEBUG
	CFLAGS += -g
endif

all: $(NAME)

%.o: %.c $(HEADERS) Makefile
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test: all
	./$(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	all bonus clean fclean re test
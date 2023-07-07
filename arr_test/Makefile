CC=cc
CFLAGS=-I include -I include/defs
NAME=array
SRC=main.c array.c split.c wildcard.c string.c assoc.c memory.c global.c env.c
OBJ=$(SRC:.c=.o)
DEFS=arraydef.h assocdef.h globaldef.h strdef.h
HEADERS=$(DEFS) array.h assoc.h env.h global.h memory.h str.h

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
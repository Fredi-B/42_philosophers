NAME = philosophers

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
ODIR = o-files
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
UNAME_S := $(shell uname -s)
CFILES = main.c parsing.c libft_utils.c free_data.c \
			init_mutexes.c init_threads.c routine.c \
			eat.c sleep_and_think.c

$(NAME): $(OBJECTS)
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/,$(OBJECTS)) -o $(NAME) -lpthread
else
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/,$(OBJECTS)) -o $(NAME)
endif

%.o: %.c
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) -c $< -o $(ODIR)/$@
else
	$(CC) $(CFLAGS) -c $< -o $(ODIR)/$@ 
endif


.phony: all
all: $(NAME)

.phony: clean
clean:
	rm -f $(ODIR)/*.o

.phony: fclean
fclean:
	rm -f $(NAME) *~

.phony: re
re: fclean all

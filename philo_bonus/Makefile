NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
ODIR = o-files
UNAME_S := $(shell uname -s)
CFILES = main_bonus.c parsing_bonus.c libft_utils_bonus.c time_bonus.c \
		routine_bonus.c eat_bonus.c print_bonus.c
OBJECTS := $(patsubst %.c,%.o,$(CFILES))
OBJECTS := $(addprefix $(ODIR)/,$(OBJECTS))

$(NAME): $(OBJECTS)
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lpthread
else
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
endif

$(ODIR)/%.o: %.c
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) -c $< -o $@
else
	$(CC) $(CFLAGS) -c $< -o $@ 
endif

.phony: all
all: $(NAME)

.phony: bonus
bonus: all

.phony: clean
clean:
	rm -f $(OBJECTS)

.phony: fclean
fclean: clean
	rm -f $(NAME) *~

.phony: re
re: fclean all

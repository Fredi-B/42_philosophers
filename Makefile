# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 16:11:33 by fbechtol          #+#    #+#              #
#    Updated: 2022/04/12 13:35:35 by fbechtol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
ODIR = o-files
UNAME_S := $(shell uname -s)
CFILES = main.c parsing.c libft_utils.c free_data.c \
			init_mutexes.c init_pointer.c init_threads.c \
			routine.c eat.c sleep_and_think.c doctor.c \
			time.c
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

.phony: clean
clean:
	rm -f $(OBJECTS)

.phony: fclean
fclean: clean
	rm -f $(NAME) *~

.phony: re
re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 16:11:33 by fbechtol          #+#    #+#              #
#    Updated: 2022/04/11 16:11:34 by fbechtol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = gcc -g #-fsanitize=thread
CFLAGS = -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
ODIR = o-files
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
UNAME_S := $(shell uname -s)
CFILES = main.c parsing.c libft_utils.c free_data.c \
			init_mutexes.c init_pointer.c init_threads.c \
			routine.c eat.c sleep_and_think.c doctor.c \
			time.c

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

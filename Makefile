NAME = philosophers

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-g -ggdb3 -fsanitize=address
# -L followed by the relative path of the library to link it 
CFILES = \
main.c

ODIR = o-files
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
UNAME_S := $(shell uname -s)
$(NAME): $(OBJECTS)
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/,$(OBJECTS)) -o $(NAME)
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

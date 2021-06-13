##########################################################################################
NAME :=	minishell

OS = $(shell uname)
USER = $(shell whoami)

SRCPATH := src
SRC := $(shell find $(SRCPATH) -name *.c)

VPATH := $(SRCPATH) 

OBJPATH := obj
OBJDIR := $(subst $(SRCPATH), $(OBJPATH), $(shell find $(SRCPATH) -type d))
OBJ := $(subst $(SRCPATH), $(OBJPATH), $(SRC:.c=.o))


LIBFT := lib/libft/libft.a
LIB := $(LIBFT)
LIB += -lreadline

ifeq ($(OS), Darwin)
LIB += -LUsers/$(USER)/.brew/Cellar/readline/8.1/lib/
endif

INC := -Iinclude/ -Ilib/libft/include 
############################################################################################
 #_____    _____    _____ 
#/ ____|  / ____|  / ____|
#| |  __  | |      | |     
#| | |_ | | |      | |     
#| |__| | | |____  | |____ 
 #\_____|  \____|  \_____|
CC := gcc
CFLAGS := -g3 -Wall -Wextra -Werror --std=c99#  -fsanitize=address 
############################################################################################

all: $(NAME)


$(NAME): $(LIBFT) $(OBJPATH) $(OBJ)
	@echo -n "\033[1;32m"
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)
	@echo "\n===========>   $(NAME) Successfully compiled"
	@echo -n "\033[1;0m"

$(OBJPATH)/%.o: %.c
	@echo -n "\033[1;32m"
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;0m"

$(OBJPATH):
	@echo -n "\033[1;32m"
	mkdir -p $(OBJDIR)
	@echo -n "\033[1;0m"

$(LIBFT):
	@echo -n "\033[1;32m"
	make -C $(dir $(LIBFT))
	@echo -n "\033[1;0m"

clean:
	@echo -n "\033[1;31m"
	make clean -C $(dir $(LIBFT))
	rm -rf $(OBJPATH)
	@echo -n "\033[1;0m"

fclean: clean
	@echo -n "\033[1;31m"
	make fclean -C $(dir $(LIBFT))
	rm -rf $(NAME)
	@echo -n "\033[1;0m"

re: fclean all

.PHONY: test re fclean clean all

############################################################################################
test: $(NAME) 
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(NAME)

echo:
	@echo $(OBJDIR)
	@echo $(OBJ)
	@echo $(SRC)
###########################################################################################

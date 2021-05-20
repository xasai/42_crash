##########################################################################################
NAME :=	minishell

SRCPATH := src
SRC := $(shell find $(SRCPATH) -name *.c)

VPATH := $(SRCPATH) 

OBJPATH := obj
OBJDIR := $(subst $(SRCPATH), $(OBJPATH), $(shell find $(SRCPATH) -type d))
OBJ := $(subst $(SRCPATH), $(OBJPATH), $(SRC:.c=.o))


LIBFT := lib/libft/libft.a
LIB := -ltermcap $(LIBFT)

INC := -Iinclude/ -Ilib/libft/include
############################################################################################
CC := gcc#	 											  #_____    _____    _____ 
CFLAGS := -g3 -Wall -Wextra -Werror --std=c99# 			#/ ____|  / ____|  / ____|
														#| |  __  | |      | |     
														#| | |_ | | |      | |     
														#| |__| | | |____  | |____ 
														 #\_____|  \____|  \_____|
############################################################################################

all: $(NAME)

echo:
	@echo $(OBJDIR)
	@echo $(OBJ)
	@echo $(SRC)

$(NAME): $(LIBFT) $(OBJPATH) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)

$(OBJPATH)/%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(OBJPATH):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(dir $(LIBFT))

clean:
	make clean -C $(dir $(LIBFT))
	rm -rf $(OBJPATH)

fclean: clean
	make fclean -C $(dir $(LIBFT))
	rm -rf $(NAME)

re: fclean all

.PHONY: test re fclean clean all

############################################################################################
test: $(NAME) 
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(NAME)
############################################################################################

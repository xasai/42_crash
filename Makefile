##########################################################################################
NAME :=	minishell

SRCPATH := src/
SRC := $(notdir $(shell find $(SRCPATH) -name *.c))
SRC := $(addprefix $(SRCPATH), $(SRC))

VPATH := $(SRCPATH)

OBJPATH := obj/
OBJDIR := $(subst $(SRCPATH), $(OBJPATH), $(shell find $(SRCPATH)* -type d))
OBJ := $(subst $(SRCPATH), $(OBJPATH), $(SRC:.c=.o))

LIBFT := lib/libft/libft.a

############################################################################################
CC := gcc#	 											  #_____    _____    _____ 
CFLAGS := -g3 -Wall -Wextra -Werror --std=c99# 			#/ ____|  / ____|  / ____|
INC := -Iinclude/ -Ilib/libft/include#					#| |  __  | |      | |     
LIB := -ltermcap -Llib/libft -lft#						#| | |_ | | |      | |     
														#| |__| | | |____  | |____ 
														 #\_____|  \____|  \_____|
############################################################################################
TEST := test
TEST_OBJ := $(TEST_SRC:.c=.o)
############################################################################################

all: $(NAME)

############################################################################################
$(TEST): $(NAME) 
	@./$(NAME)

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)#

debug: $(NAME)
	gdb	./$(NAME)
############################################################################################

$(NAME): $(LIBFT) $(OBJPATH) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)

$(OBJPATH)%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(OBJPATH):
	mkdir -p $(OBJPATH) $(OBJDIR)

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

CCF = gcc -Wall -Wextra -Werror -g
NAME = libft.a

INC = -Iinclude/
SRC =	$(addprefix src/, \
		ft_atoi.c     ft_isalpha.c      ft_itoa.c     ft_memset.c       ft_putstr.c     ft_strjoin.c  ft_strnstr.c\
		ft_bzero.c    ft_isascii.c      ft_memccpy.c  ft_putchar.c      ft_putstr_fd.c  ft_strlcat.c  ft_strrchr.c\
		ft_calloc.c   ft_isdigit.c      ft_memchr.c   ft_putchar_fd.c   ft_skip_atoi.c  ft_strlcpy.c  ft_strtrim.c\
		ft_ctod.c     ft_isempty_str.c  ft_memcmp.c   ft_putendl_fd.c   ft_split.c      ft_strlen.c   ft_substr.c\
		ft_intwid.c   ft_isprint.c      ft_memcpy.c   ft_putnbr_base.c  ft_strchr.c     ft_strmapi.c  ft_tolower.c\
		ft_isalnum.c  ft_isspace.c      ft_memmove.c  ft_putnbr_fd.c    ft_strdup.c     ft_strncmp.c  ft_toupper.c\
		get_next_line_utils.c			get_next_line.c)

OBJ = $(subst src/,obj/,$(SRC:.c=.o))
HDR = include/libft.h
OBJDIR = obj/
VPATH = src

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDR) 
	ar rc $(NAME) $(OBJ) 

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c
	$(CCF) $(INC) -c $< -o $@ 

clean: 
	rm -rf $(OBJDIR)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: bonus clean fclean re all


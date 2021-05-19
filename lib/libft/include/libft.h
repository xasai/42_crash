#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

typedef struct s_rem
{
	char			*string;
	ssize_t			size;
}					t_rem;

typedef struct s_gnl
{
	char			*string;
	struct s_gnl	*next;
	ssize_t			size;
}					t_gnl;

typedef struct s_head
{
	t_gnl			*head;
	t_gnl			*tail;
	ssize_t			overall_size;
}					t_head;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_read
{
	char			*buf;
	ssize_t			size;
	ssize_t			endl;
}					t_read;
/*
**============================================================
**					libft	
*/
void				ft_bzero(void *s, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
int					ft_tolower(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isspace(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_putchar(char c);
void				ft_putstr(char *s);
int					ft_ctod(char c);
int					ft_intwid(long int i, int base);
void				ft_putnbr_base(long int i, const char *base);
int					ft_skip_atoi(char **s);
int					ft_isempty_str(char *str);

/*
**============================================================
**					get_next_line
*/
int					get_next_line(int fd, char **line);
int					read_line(int fd, char **line,
						t_rem *rm, t_head **lst_head);
int					read_check(t_read r, char **line,
						t_rem *rm, t_head **lst_head);
void				*gnl_append_buff(t_head **head, char *str, ssize_t size);
char				*gnl_concat(t_head **head);
char				*gnl_strdup(char *str, ssize_t size);
int					find_endl(char *str, ssize_t size);
int					gnl_clear(t_head *head, t_rem *remainder,
						char **line, int ret);
int					rebuild_remainder(t_rem *remainder,
						int endl, char **line, t_head *lst_head);

#endif

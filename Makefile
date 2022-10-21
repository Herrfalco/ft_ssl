NAME	=	ft_ssl
SRCS	=	srcs/ft_ssl.c \
		srcs/algs/md5/md5.c \
		srcs/algs/sha224/sha224.c \
		srcs/algs/sha256/sha256.c \
		srcs/algs/sha384/sha384.c \
		srcs/algs/sha512/sha512.c \
		srcs/common/utils.c
OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -rf

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

%.o	:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

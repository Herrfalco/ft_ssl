NAME	=	ft_ssl_test
SRCS	=	expect.c \
		tests.c \
		unifiers.c \
		../utils.c \
		../algs/md5.c \
		../algs/sha224.c \
		../algs/sha256.c \
		../algs/sha384.c \
		../algs/sha512.c
OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
CFLAGS	=	-Wall -Wall -Wextra
LIBS	=	-lcrypto

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o	:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all

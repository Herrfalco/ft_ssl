NAME	=	ft_ssl_tests
SRCS	=	expect.c \
		tests.c \
		unifiers.c \
		../srcs/common.c \
		../srcs/utils.c \
		../srcs/algs/md5.c \
		../srcs/algs/sha224.c \
		../srcs/algs/sha256.c \
		../srcs/algs/sha384.c \
		../srcs/algs/sha512.c \
		../srcs/core/dispatch.c \
		../srcs/core/errors.c \
		../srcs/core/params.c
OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
CFLAGS	=	-Wall -Wall -Wextra -Wno-deprecated-declarations
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

NAME	=	sha224_test
SRCS	=	../sha256/sha256.c \
		sha224.c \
		sha224_test.c \
		../common/utils.c \
		../common/test_utils.c
OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-lcrypto
RM	=	rm -rf

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ -lcrypto

%.o	:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

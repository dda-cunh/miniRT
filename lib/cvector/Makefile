.SILENT:
NAME	= 	libcvector.a

CC 		= 	clang

AR		=	ar rcs

SRC		= 	cvector.c \
			memory.c

OBJ 	= 	$(SRC:%.c=%.o)

CFLAGS	= 	-c -Wall -Wextra -Werror

RM 		= 	rm -f

GREEN	= 	\033[0;32m

RED		=	\033[0;31m

RESET	=	\033[0m

SUS		=	\U00000D9E

HAMMER	=	\U0001F528

BROOM	=	\U0001F9F9


$(NAME):	$(OBJ)
			$(AR) $(NAME) $(OBJ)

$(OBJ): 	$(SRC)
			printf '$(HAMMER)\t'
			printf "$(GREEN)Compiling $(RED)$(NAME)$(RESET)\n"
			$(CC) $(CFLAGS) $(SRC)

all: 		$(NAME)

clean:	
			$(RM) $(OBJ) $(OBJB)

fclean:		clean
			$(RM) $(NAME)

re:			fclean	all

.PHONY: 	all clean fclean re
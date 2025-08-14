# COLORS

BROWN				=	\x1b[0m\x1b[38;2;137;81;41m
LIGHT_BROWN		=	\x1b[0m\x1b[38;2;172;133;105m
DARK_BROWN		=	\x1b[1m\x1b[38;2;96;57;29m

# TARGET

NAME			=	libasm.a

# FLAGS

MAKEFLAGS		+=	-s
AS				=	nasm
ASFLAGS			=	-f elf64
ARFLAGS			=	rcs
CC				=	gcc
CFLAGS			=	-no-pie

# FILES

FILES			=	ft_strlen ft_strcpy ft_strcmp ft_strdup	\
					ft_write ft_read						\
\

SRC				=	$(addsuffix .s, $(FILES))
OBJ				=	$(addsuffix .o, $(FILES))

# TESTS

FILES_TEST		=	test

SRC_TEST		=	$(addsuffix .c, $(FILES_TEST))
OBJ_TEST		=	$(addsuffix .o, $(FILES_TEST))


# RULES

all:			$(NAME)

$(NAME):		$(OBJ)
				$(AR) $(ARFLAGS) $(NAME) $^
				echo -e '$(LIGHT_BROWN) \tCompiled$(DARK_BROWN) $(NAME)$(LIGHT_BROWN) that include$(BROWN) $(FILES)'

clean:
				rm -f $(OBJ) $(OBJ_TEST)
				echo -e '$(LIGHT_BROWN) \tCleaned$(BROWN) $(OBJ)'

fclean:			clean
				rm -f $(NAME) test
				echo -e '$(LIGHT_BROWN) \tCleaned$(DARK_BROWN) $(NAME)'

re:				fclean all

test:			$(OBJ_TEST) $(NAME)
				$(CC) $(CFLAGS) $^ -o $@
				echo -e '$(LIGHT_BROWN) \tCompiled$(DARK_BROWN) $(FILES_TEST)$(LIGHT_BROWN) using$(DARK_BROWN) $(NAME)'

.PHONY:			all bonus clean fclean re test

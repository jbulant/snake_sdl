NAME = snake

DEBUG = 0

LIBFTDIR = libft/

LIBFT_NAME = libft.a

LIBFT = $(LIBFTDIR)$(LIBFT_NAME)

SRCS_DIR =	\

SRCS_NAME = \
			main.c \

INCLUDES =	\
			-Iincludes \


LIBS =	-ltermcap -L $(LIBFTDIR) -lft

HEADERS_PATH =	includes/
HEADERS_NAME =	\


CC = gcc

OBJ_VDIR = $(addprefix $(OBJ_ROOTDIR), $(SRCS_DIR))
SRCS = $(addprefix $(SRCS_ROOTDIR),$(SRCS_NAME))
OBJS = $(addprefix $(OBJ_ROOTDIR),$(SRCS_NAME:.c=.o))
HEADERS = $(addprefix $(HEADERS_PATH), $(HEADERS_NAME))

OBJ_ROOTDIR = objs/
SRCS_ROOTDIR = srcs/
GFLAGS = 
CFLAGS = -Wall -Wextra -Werror $(GFLAGS)
DEBUGFLAGS = -g3 -fsanitize=address

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@if [ $(DEBUG) -eq 1 ];\
	then\
		$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(LIBS);\
	else\
		$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS);\
	fi
	@printf "\r \360\237\215\272 PROGAM [\e[0;31m %s \e[0m] HAS BEEN COMPILED.\e[K\n" \
	`echo $(NAME) | tr a-z A-Z`

$(OBJ_ROOTDIR)%.o: $(SRCS_ROOTDIR)%.c ${HEADERS}
	@mkdir -p $(OBJ_ROOTDIR) $(OBJ_VDIR)
	@if [ $(DEBUG) -eq 1 ];\
	then\
		printf "\r   [\e[0;31m %s - \e[1;33mDEBUG\e[0m ] converting \e[1;31m%s\e[0m\e[K" \
		`echo $(NAME) | tr a-z A-Z` \
		`echo $< | sed 's/^srcs\///g' | sed 's/\.c$///g'`;\
		$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c -o $@ $<;\
		printf "\r \e[0;32m\xE2\x9C\x94\033[0m [\e[0;31m %s - \e[1;33mDEBUG\e[0m ] converting \e[1;31m%s\e[0m\e[K" \
		`echo $(NAME) | tr a-z A-Z` \
		`echo $< | sed 's/^srcs\///g' | sed 's/\.c$///g'`;\
	else\
		printf "\r   [\e[0;31m %s \e[0m] converting \e[1;31m%s\e[0m\e[K" \
		`echo $(NAME) | tr a-z A-Z` \
		`echo $< | sed 's/^srcs\///g' | sed 's/\.c$///g'`;\
		$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<;\
		printf "\r \e[0;32m\xE2\x9C\x94\033[0m [\e[0;31m %s \e[0m] converting \e[1;31m%s\e[0m\e[K" \
		`echo $(NAME) | tr a-z A-Z` \
		`echo $< | sed 's/^srcs\///g' | sed 's/\.c$///g'`;\
	fi

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_ROOTDIR)


fclean: clean
	@rm -f $(NAME)

re: fclean all

#*************************************************************************** #
#                                                                              #
#            :::      ::::::::                                                 #
#          :+:      :+:    :+:                                                 #
#        +:+ +:+         +:+         Makefile v2.0                             #
#      +#+  +:+       +#+                                                      #
#    +#+#+#+#+#+   +#+               By: troberts <troberts@student.42.fr>     #
#         #+#    #+#                                                           #
#        ###   ########.fr                                                     #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              VARIABLE REFERENCE                              #
# **************************************************************************** #

NAME= philo

# CC= clang
CFLAGS= -Wall -Werror -Wextra -g3 $(INCLUDE) -fsanitize=address
LDFLAGS= -L$(LIBFT_DIR) -fsanitize=address
DEPFLAGS= -MT $@ -MMD -MP -MF $(DEP_DIR)$*.d

INCLUDE = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

LIBFT_DIR= libft
LIBFT_LIB= $(LIBFT_DIR)/libft.a

INCLUDE_DIR= include
OBJ_DIR= obj/
SRC_DIR= src/
DEP_DIR= dep/
# **************************************************************************** #
#                                .C & .H FILES                                 #
# **************************************************************************** #

SRC_FILE=	\
			main.c

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ_FILE= 	$(SRC_FILE:.c=.o)
OBJ=		$(addprefix $(OBJ_DIR), $(OBJ_FILE))
DEP_FILE=	$(SRC_FILE:.c=.o)
DEP=		$(addprefix $(DEP_DIR), $(DEP_FILE))
#OBJ=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# **************************************************************************** #
#                                HEADER CONFIG                                 #
# **************************************************************************** #

#                 # <-- start here         | <-- middle             # <-- stop here
HEADER_NAME 	= +                      Philo                      #

COLOR_RED		= \033[0;31m
COLOR_GREEN		= \033[0;32m
COLOR_YELLOW	= \033[0;33m
COLOR_BLUE		= \033[0;34m
COLOR_PURPLE	= \033[0;35m
COLOR_CYAN		= \033[0;36m
COLOR_WHITE		= \033[0;37m
COLOR_END		= \033[m

HEADER =			@echo "${COLOR_CYAN}\
					\n/* ************************************************************************** */\
					\n/*                                                                            */\
					\n/*            :::      ::::::::                                               */\
					\n/*          :+:      :+:    :+:                                               */\
					\n/*        +:+ +:+         +:${HEADER_NAME}*/\
					\n/*      +\#+  +:+       +\#+                                                    */\
					\n/*    +\#+\#+\#+\#+\#+   +\#+                       Thomas Robertson                */\
					\n/*         \#+\#    \#+\#                     <troberts@student.42.fr>            */\
					\n/*        \#\#\#   \#\#\#\#\#\#\#\#.fr                                                   */\
					\n/*                                                                            */\
					\n/* ************************************************************************** */\
					\n \
					\n \
					\n NAME: $(NAME) \
					\n \
					\n CC: $(CC) \
					\n CFLAGS: $(CFLAGS) \
					\n LDFLAGS: $(LDFLAGS) \
					\n${COLOR_END}"

HEADER_COMPIL =	@echo "${COLOR_YELLOW}\
					\n/* ************************************************************************** */\
					\n/*                                 COMPILING...                               */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_CLEAN =		@echo "${COLOR_RED}\
					\n/* ************************************************************************** */\
					\n/*                                 CLEANING...                                */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_FCLEAN =		@echo "${COLOR_RED}\
					\n/* ************************************************************************** */\
					\n/*                              FORCE CLEANING...                             */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_NORM =		@echo "${COLOR_PURPLE}\
					\n/* ************************************************************************** */\
					\n/*                            CHECKING THE NORM...                            */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_ENTERLIB =	@echo "${COLOR_GREEN}\
					\n/* ************************************************************************** */\
					\n/*                               ENTERING LIBFT                               */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

HEADER_EXITLIB =	@echo "${COLOR_GREEN}\
					\n/* ************************************************************************** */\
					\n/*                                EXITING LIB                                 */\
					\n/* ************************************************************************** */\n\
					${COLOR_END}"

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	$(HEADER)
	$(HEADER_COMPIL)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBFT_LIB)

malloc_test: $(LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJ) $(LIBFT_LIB) -L. -lmallocator

bonus: $(NAME)

$(LIBFT_LIB): makelibf ;

makelibf :
	$(HEADER_ENTERLIB)
	@make -C $(LIBFT_DIR)
	$(HEADER_EXITLIB)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(DEP): | $(DEP_DIR)
# 
# $(DEP_DIR):
# 	mkdir -p $@
# 
# $(DEP): $(SRC_DIR)%.c
# 	$(CC) $(CFLAGS) -MM -MF $@ -MT $(OBJ_DIR)$*.o $<
# 
header:
	$(HEADER)

cleanobj:
	${HEADER_CLEAN}
	rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_COMMON)

cleanobjdir: cleanobj
	rm -rf $(OBJ_DIR)

clean: header cleanobjdir cleanlibft
	
cleanlibft:
	make -C $(LIBFT_DIR) clean

fcleanlibft:
	make -C $(LIBFT_DIR) fclean

fclean: header clean fcleanlibft
	${HEADER_FCLEAN}
	rm -f $(NAME) $(NAME_BONUS)

re: header fclean all

reobj: cleanobj
	make -C .

norm: header
	${HEADER_NORM}
	@echo "$(COLOR_GREEN)"
	-python3 -m norminette $(LIBFT_DIR) | awk "!/: OK!/"
	@echo "$(COLOR_CYAN)"
	-python3 -m norminette $(SRC_DIR)
	@echo "$(COLOR_PURPLE)"
	-python3 -m norminette $(INCLUDE_DIR)
	@echo "$(COLOR_END)"

.PHONY: all clean fclean re reobj norm header makelibf cleanobj cleanobjdir fcleanlibft bonus

# include $(DEP)

# DEP_CFLAGS=-MM -MD
# ALL_CFLAGS=-I ./inc -Wall -Wextra -Werror
# src=$(wildcard *.c)
# dep=$(src:.c=.d)
# 
# ... (other flags, other rules like all etc.)
# 
# %.o:%.c
#     $(CC) -c $< $(ALL_CFLAGS) -o $@
# %.d:%.c
#     $(CC) $< $(DEP_FLAGS) $(ALL_CFLAGS) -o $@
# 
# ... (other rules etc.)
# 
# #This below has to be at the end of the Makefile, else it does not work
# -include $(dep)
##
## Makefile for cpp_nanotekspice in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice
## 
## Made by Valerian Polizzi
## Login   <polizz_v@epitech.net>
## 
## Started on  Mon Feb  8 01:08:34 2016 Valerian Polizzi
## Last update Fri Feb 26 05:49:23 2016 Valerian Polizzi
##

NAME            =               nanotekspice

LIB_NAME	=		libnanotekspice.a

LIB_SRC		=		src/Parser.cpp			\
				src/NTSException.cpp		\
				src/ComponentManager.cpp	\
				src/Component.cpp		\
				src/Lexer.cpp			\
				src/Comp4001.cpp		\

CXXFLAGS	+=		-I./include -std=c++11 -W -Werror -Wextra

NTSFLAGS	=		-Wall -W -Werror

SRC		=		src/main.cpp

LIB_OBJ    	=	        $(LIB_SRC:.cpp=.o)

OBJ		=		$(SRC:.cpp=.o)

MR_CLEAN        =               find ./ \( -name "*~" -o -name "\#*\#" \) -delete

RM              =               rm -f

SUCCESS_MSG     =               @echo -e "\033[32mSuccessful Compilation: $(NAME) generated\033[00m\a"

all             :               $(LIB_NAME) $(NAME)

$(LIB_NAME)     :               $(LIB_OBJ)
				$(MR_CLEAN)
				ar rc $(LIB_NAME) $(LIB_OBJ)
				ranlib $(LIB_NAME)
				mv $(LIB_NAME) lib/

$(NAME)		:		$(OBJ)
				g++ $(OBJ) -o $(NAME) -L./lib -lnanotekspice $(CXXFLAGS) $(LDFLAGS)

clean           :
				rm -f $(OBJ) $(LIB_OBJ)

fclean          :               clean
				rm -f  $(NAME) ./lib/$(LIB_NAME)

re              :               clean all

.PHONY          :               all clean fclean re

CXX			=	clang++

NAME		=	a.out

HEAD		=	-I ./

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g

SRCS		=	$(wildcard *.cpp)

OBJS		=	${SRCS:.cpp=.o}

$(NAME)		:	${OBJS}
				@${CXX} ${CXXFLAGS} ${HEAD} ${OBJS} -o ${NAME}

all			:	$(NAME)

clean		:
				@rm -f $(OBJS)

fclean		:	clean
				@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re

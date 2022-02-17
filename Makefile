#MAKEFLAGS += --silent

NAME = ft_containers
CC = c++
CPPFLAGS = -g3 -Wextra -Wall -Werror
INC_DIR = ./
INC =

SRC_DIR = ./
SRC =	main.cpp \

OBJ_DIR = .obj/
OBJ = $(SRC:%.cpp=$(OBJ_DIR)%.o)

.PHONY : all clean fclean re exec

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(addprefix $(INC_DIR),$(INC))
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -I$(INC_DIR) -c $< -o $@

exec:
	./$(NAME)

norm:
	norminette

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all

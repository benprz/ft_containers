#MAKEFLAGS += --silent

NAME = ft_containers
CC = c++
CPPFLAGS = -fsanitize=address #-std=c++98#-Wextra -Wall -Werror
#CPPFLAGS += -fsanitize=address -g3
INC_DIR = inc/
INC =	map.hpp \
		map_tree.hpp	

SRC_DIR = src/
SRC = test_map.cpp

OBJ_DIR = .obj/
OBJ = $(SRC:%.cpp=$(OBJ_DIR)%.o)

.PHONY : all clean fclean re exec

all: $(NAME) exec

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(addprefix $(INC_DIR),$(INC))
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -I$(INC_DIR) -c $< -o $@

exec:
	./$(NAME)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all

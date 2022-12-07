NAME = AdventOfCode
PROJECT_NAME = ADVENTOFCODE

#FILES
FILES = main.cpp

#PATHS
OBJ_DIR = object

#OBJECTS
OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:.cpp=.o))

#MISCELLANEOUS
DEBUGFLAGS = -O3
PREPROCFLAGS = $(DEBUGFLAGS)
LINKERFLAGS =
CC = g++
CFLAGS = -Wall -Wextra -Werror $(DEBUGFLAGS)

##	VISUALS	##
_BANNER = \033[1m\033[34m[$(PROJECT_NAME)]\033[39m
_BUILDBANNER = $(_BANNER)\033[32m[BUILD]\033[39m —\033[0m
_CLEANBANNER = $(_BANNER)\033[33m[REMOVED]\033[39m —\033[0m

##	RULES	##
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.cpp $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(PREPROCFLAGS) -c $< -o $@
	@echo "$(_BUILDBANNER) $@"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "$(_BUILDBANNER) $@ folder"

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LINKERFLAGS)
	@echo "$(_BUILDBANNER) $@"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(_CLEANBANNER) $(OBJ_DIR) folder"
	
fclean: clean
	@rm -f $(NAME)
	@echo "$(_CLEANBANNER) $(NAME)"
	
re: fclean all

nice: all clean
	@clear
	@echo "\033[34m\033[1m[NICE]\033[39m —\033[0m clear"

.PHONY: clean fclean all re nice

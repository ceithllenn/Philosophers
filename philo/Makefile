NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -lm
INCLUDES = -I .

SRCS_DIR = src/


FUNC =	

MAIN = main.c $(FUNC)

SRCS_PUSH = $(addprefix $(SRCS_DIR), $(MAIN))
SRCS_CHECKER = $(addprefix $(SRCS_DIR), $(FUNC))

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_PUSH:.c=.o)))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_CHECKER:.c=.o)))

# Rule to compile .c files to .o files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $< to $@"
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the final executable
$(NAME): $(OBJS) 
	@echo "Linking $(NAME)"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	
# Clean object files
clean:	rm -rf $(OBJS_DIR)

# Full clean
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Default target
all: $(NAME)

.PHONY: all clean fclean re
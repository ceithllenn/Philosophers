NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -MMD
INCLUDES = -I .

SRCS_DIR = src/

FUNC =  arguments.c \
		exit.c \
		init.c \
		monitoring.c \
		philo_routine.c \
		utils.c

MAIN = main.c $(FUNC)

SRCS_PUSH = $(addprefix $(SRCS_DIR), $(MAIN))

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_PUSH:.c=.o)))

DEPS = $(OBJS:.o=.d)

# Rule to compile .c files to .o files and generate dependency files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $< to $@"
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the final executable
$(NAME): $(OBJS)
	@echo "Linking $(NAME)"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

# Clean object files and dependency files
clean:
	rm -rf $(OBJS_DIR)

# Full clean
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Default target
all: $(NAME)

.PHONY: all clean fclean re

# Include dependency files
-include $(DEPS)
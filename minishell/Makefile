.SILENT:

YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs

OBJS_DIR = objs

SRCS =

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)What the shell, it compile!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -I$(PRINTF_DIR) -I$(LIBFT_DIR) -g3 -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

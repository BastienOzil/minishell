.SILENT:

YELLOW = \033[1;33m
GREEN  = \033[1;32m
RESET  = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

OBJ_DIR = objs
LIBFT_DIR = utils/libft
ANIMATION_DIR = animation

SRCS = main.c \
	srcs/exec/executor.c \
	srcs/exec/exec_path.c \
	srcs/exec/path_utils.c \
	srcs/exec/run_execve.c \
	srcs/exec/redir_output.c \
	srcs/exec/redir_input.c \
	srcs/exec/redir_append.c \
	srcs/exec/pipe.c \
	srcs/exec/exec_builtins.c \
	srcs/exec/heredoc.c \
	srcs/exec/pipe/pipe_exec.c \
	srcs/exec/pipe/pipe_redir.c \
	srcs/exec/pipe/pipe_run.c \
	srcs/exec/pipe/pipe_utils.c \
	srcs/parse/cleanup.c \
	srcs/parse/cleanup2.c \
	srcs/parse/error_messages.c \
	srcs/parse/expansion.c \
	srcs/parse/expansion2.c \
	srcs/parse/handle_line.c \
	srcs/parse/handle_line2.c \
	srcs/parse/lexer_cmd.c \
	srcs/parse/lexer_cmd2.c \
	srcs/parse/lexer.c \
	srcs/parse/lexer2.c \
	srcs/parse/lexer3.c \
	srcs/parse/logical_ops.c \
	srcs/parse/parser_error.c \
	srcs/parse/parser_utils.c \
	srcs/parse/parser_utils2.c \
	srcs/parse/parser_utils3.c \
	srcs/parse/parser_utils4.c \
	srcs/parse/parser.c \
	srcs/parse/parser2.c \
	srcs/parse/print_token.c \
	srcs/parse/quote_parser.c \
	srcs/parse/utils.c \
	srcs/parse/vanish.c \
	srcs/parse/wildcard.c \
	srcs/builtins/cd_utils.c \
	srcs/builtins/builtin_cd.c \
	srcs/builtins/builtin_echo.c \
	srcs/builtins/echo_utils.c \
	srcs/builtins/builtin_env.c \
	srcs/builtins/builtin_exit.c \
	srcs/builtins/export_utils.c \
	srcs/builtins/builtin_export.c \
	srcs/builtins/builtin_pwd.c \
	srcs/builtins/builtin_unset.c \
	srcs/builtins/env_util.c \
	srcs/builtins/env_dup.c \
	srcs/signals/signal_handler.c \
	srcs/signals/signal_setup.c \
	srcs/signals/signal_setup2.c \
	srcs/signals/signal_utils.c \
	srcs/signals/signal_utils2.c 

OBJ_FILES = $(notdir $(SRCS:.c=.o))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))


LIBFT = $(LIBFT_DIR)/libft.a
ANIMATION_LIB = $(ANIMATION_DIR)/animation.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(ANIMATION_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(ANIMATION_LIB) -o $(NAME) $(LFLAGS)
	echo "$(GREEN)"
	echo "                   /\\                     "
	echo "      G H O S T   /in\\   M I N I S H E L L"
	echo "                 / The\\                   "

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: srcs/builtins/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/exec/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/exec/pipe/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/parse/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: srcs/signals/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(ANIMATION_DIR)/includes -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(ANIMATION_LIB):
	@make -s -C $(ANIMATION_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(ANIMATION_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(ANIMATION_DIR)

re: fclean all

.PHONY: all clean fclean re

NAME := cub3d 
CFLAGS :=
# CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -Ofast -O3
LIBMLX := ./MLX42

HEADERS := -I ./ -I ./libft -I $(LIBMLX)/include/MLX42
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
MANDATORY_SRCS     := main.c
MANDATORY_OBJS_DIR := ./objects/
MANDATORY_SRCS_OBJS:= ${MANDATORY_SRCS:.c=.o}
MANDATORY_OBJS     := $(addprefix $(MANDATORY_OBJS_DIR), $(MANDATORY_SRCS_OBJS))

# Libft
LIBFT_NAME = libft.a
LIBFT_DIR := ./libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

bonus: all

$(NAME): $(MANDATORY_OBJS_DIR) $(MANDATORY_OBJS)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

$(MANDATORY_OBJS_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(MANDATORY_OBJS_DIR):
	@mkdir -p $(MANDATORY_OBJS_DIR)

clean:
	@rm -rf $(MANDATORY_OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	@rm -rf $(MANDATORY_OBJS_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(LIBMLX)/build
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re


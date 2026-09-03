NAME = cub3d 

CC = cc
CFLAGS := -g
RM = rm -f

# CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -Ofast -O3
MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include

HEADERS := cub3d.h
MANDATORY_SRCS     := main.c \
					  parse_file.c \
					  colour.c \
					  init.c \
					  draw.c \
					  frame.c \
					  moves.c \
					  keyhooks.c \
					  utils.c

MANDATORY_OBJS_DIR := ./objects/
MANDATORY_SRCS_OBJS:= ${MANDATORY_SRCS:.c=.o}
MANDATORY_OBJS     := $(addprefix $(MANDATORY_OBJS_DIR), $(MANDATORY_SRCS_OBJS))

INC_DIR = ./

# Libft
LIBFT_NAME = libft.a
LIBFT_DIR = ./libft
LIBFT_INC := -I$(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

INCLUDES	= -I$(INC_DIR) $(MLX_INC) $(LIBFT_INC)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_FLAGS = -ldl -lglfw -pthread -lm
endif

ifeq ($(UNAME_S), Darwin)
	GLFW_PATH = $(shell brew --prefix glfw)
	MLX_FLAGS = -lglfw -L$(GLFW_PATH)/lib \
                -framework Cocoa -framework OpenGL -framework IOKit
endif

all: $(NAME)

bonus: all

$(NAME): $(MANDATORY_OBJS_DIR) $(MANDATORY_OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(MANDATORY_OBJS_DIR)%.o: %.c $(HEADERS) | $(MANDATORY_OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< 

$(MANDATORY_OBJS_DIR):
	@mkdir -p $(MANDATORY_OBJS_DIR)

$(MLX_LIB):
	@cmake -B $(MLX_DIR)/build -S $(MLX_DIR)
	@cmake --build $(MLX_DIR)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(MANDATORY_OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) -r $(MANDATORY_OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) -r $(NAME)

fclean_all: fclean
	$(RM) -r $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean fclean_all re


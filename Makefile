NAME := miniRT

CC := cc
RM := rm -rf
CFLAGS := -Wall -Werror -Wextra
LIBS := -ldl -lglfw -pthread -lm

SRC_DIR := src
OBJ_DIR := obj
MINIRT_INC := -Iinclude

SRC_FILES := main.c vec_op.c parsing.c  math_utils.c \
			test_utils.c test_main.c dummy_utils.c matrix_op.c \
			vec_mtx_op.c op_ray.c op_obj.c op_mtx_mov.c \
			world_utils.c world_inter.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

MLX_PATH := ./MLX42
MLX_LIB := $(MLX_PATH)/build/libmlx42.a
MLX_INC := -I$(MLX_PATH)/include/MLX42/
MLX_REPO := https://github.com/codam-coding-college/MLX42.git

LIB_REPO_PASS := https://github.com/oishchen42/42_lib_mix
LIBNAME = mixlibft
LIBNAME_A = $(LIBNAME)/mixlibft.a
MIX_INCLUDE := -I$(LIBNAME)/libft/includes/ \
		-I$(LIBNAME)/printf/includes/ \
		-I$(LIBNAME)/get_next_line/includes/

$(NAME) : $(OBJ) $(MLX_LIB) | $(LIBNAME_A)
	$(CC) $(CFLAGS) $(MLX_INC) $(MINIRT_INC) $(MIX_INCLUDE) $(OBJ) $(MLX_LIB) $(LIBNAME_A) $(LIBS) -o $(NAME)

all: $(NAME) | $(LIBNAME) $(MLX_PATH)

$(MLX_LIB):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "MLX42 was not found. Cloning from the $(MLX_REPO)..."; \
		git clone $(MLX_REPO) $(MLX_PATH); \
	else \
		echo "MLX42 directory found."; \
	fi

	@echo "Building MLX42..." 
	@cmake -S $(MLX_PATH) -B $(MLX_PATH)/build
	@cmake --build $(MLX_PATH)/build -j4

$(LIBNAME):
	@if [ ! -d $(LIBNAME) ]; then \
		echo "CLONING LIBRARY_REPO"; \
		git clone $(LIB_REPO_PASS) $(LIBNAME); \
	else \
		echo "REPOSITORY EXISTS"; \
	fi

$(LIBNAME_A): $(LIBNAME)
	make -C $(LIBNAME);

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(MLX_LIB) $(LIBNAME)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(MLX_INC) $(MIX_INCLUDE) $(MINIRT_INC) -c $< -o $@

clean:
	@make clean -C $(LIBNAME)
	@$(RM) $(OBJ_DIR)
	@echo "OBJECTS CLEANED"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBNAME)
	@echo "FULL CLEAN COMPLETE"

re: fclean all

.PHONY: all clean fclean re
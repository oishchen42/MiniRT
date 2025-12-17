NAME := miniRT

CC := cc
RM := rm -rf
CFLAGS := -Wall -Werror -Wextra
LIBS := -ldl -lglfw -pthread -lm

SRC_DIR := src
OBJ_DIR := obj
MINIRT_INC = include

SRC_FILES := camera_1.c camera_2.c control.c dummy_utils.c light_shd_1.c \
			light_shd_2.c main.c math_utils.c matrix_op_1.c matrix_op_2.c \
			op_mtx_mov_1.c op_mtx_mov_2.c op_mtx_mov_3.c op_obj_1.c \
			op_obj_2.c op_obj_3.c op_ray_1.c op_ray_2.c parse_data.c \
			parse_file.c parse_main.c parse_obj.c parse_orient.c \
			parse_test.c parsing.c render.c test_main.c test_utils_1.c \
			test_utils_2.c test_utils_3.c vec_mtx_op.c vec_op_1.c \
			vec_op_2.c world_inter.c world_utils.c resize_hook.c

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

$(NAME) : $(OBJ) $(MLX_LIB) $ | $(LIBNAME_A)
	$(CC) $(CFLAGS) $(MLX_INC) -I$(MINIRT_INC) $(MIX_INCLUDE) $(OBJ) $(MLX_LIB) $(LIBNAME_A) $(LIBS) -o $(NAME)

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
	$(CC) $(CFLAGS) $(MLX_INC) $(MIX_INCLUDE) -I$(MINIRT_INC) -c $< -o $@

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
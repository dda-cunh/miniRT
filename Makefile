.SILENT:
NAME		=	miniRT

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

RM			=	rm -rf

INC_DIR		=	inc/

SRC_DIR		=	src/

OBJ_DIR		=	temp/

PROG_DIR	=	program/

RAY_DIR		=	raytrace/

MATH_DIR	=	math/

TYPES_DIR	=	t_types/

UTILS_DIR	=	utils/

LFT_DIR		=	libft/

LFT_FULL	=	$(addprefix $(INC_DIR), $(LFT_DIR))

LINKS		=	-L$(LFT_FULL) -lft -lXext -lX11 -lm -Linc/minilibx-linux -lmlx

SRC			=	$(addprefix $(SRC_DIR),	main.c \
										$(addprefix $(PROG_DIR),	program.c \
																	events.c) \
										$(addprefix $(RAY_DIR),		ray.c \
																	collisions.c \
																	trace.c) \
										$(addprefix $(UTILS_DIR),	color.c \
																	image.c \
																	utils.c) \
										$(addprefix $(MATH_DIR),	common.c \
																	point3.c \
																	vec3.c) \
										$(addprefix $(TYPES_DIR),	object_cylinder.c \
																	object_sphere.c \
																	object_plane.c \
																	coll_entity_list.c \
																	collidable_shape.c))

OBJ_DIRS	=	$(OBJ_DIR)	$(addprefix $(OBJ_DIR), $(PROG_DIR)) \
							$(addprefix $(OBJ_DIR), $(RAY_DIR)) \
							$(addprefix $(OBJ_DIR), $(UTILS_DIR)) \
							$(addprefix $(OBJ_DIR), $(MATH_DIR)) \
							$(addprefix $(OBJ_DIR), $(TYPES_DIR))

OBJ		=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

SCENE		=	scenes/empty.rt

GREEN		=	\033[0;32m

RED			=	\033[0;31m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ) | $(SRC)
				printf '$(HAMMER)\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(LINKS)
				make compiled

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIRS)
				make -C $(LFT_FULL)
				make bonus -C $(LFT_FULL)
				printf '$(HAMMER)\t'
				printf "$(GREEN)Compiling $(NAME) objects... $(RED)%-33.33s\r" $(notdir $@)
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIRS):
				mkdir -p $@

all:			$(NAME)

clean:
				make fclean -C $(LFT_FULL)
				if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi
				if [ -d $(DEBUG_DIR) ]; then $(RM) $(DEBUG_DIR); fi

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				$(RM) $(NAME)
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean all

compiled:
				printf "																\n"
				printf "$(GREEN)	$(NAME)										$(RESET)\n"
				printf "$(GREEN)                             _  _             _ $(RESET)\n"
				printf "$(GREEN)                            (_)| |           | |$(RESET)\n"
				printf "$(GREEN)  ____   ___   ____   ____   _ | |  ____   _ | |$(RESET)\n"
				printf "$(GREEN) / ___) / _ \ |    \ |  _ \ | || | / _  ) / || |$(RESET)\n"
				printf "$(GREEN)( (___ | |_| || | | || | | || || |( (/ / ( (_| |$(RESET)\n"
				printf "$(GREEN) \____) \___/ |_|_|_|| ||_/ |_||_| \____) \____|$(RESET)\n"
				printf "$(GREEN)                     |_|                        $(RESET)\n"
				printf "																\n"

run:			all
				./$(NAME) $(SCENE)

rerun:			fclean | run

.PHONY:		all clean fclean re run rerun

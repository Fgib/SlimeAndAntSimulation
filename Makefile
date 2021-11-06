ROOT	=		.

SRC_DIR	=		src

CC		=		gcc

NAME	=		simulation

REAL	=		$(ROOT)/build

SRC		=	$(SRC_DIR)/main.c\
			$(SRC_DIR)/hitbox.c\
			$(SRC_DIR)/effects.c\
			$(SRC_DIR)/particle.c\
			$(SRC_DIR)/helpers/math_trigo.c\
			$(SRC_DIR)/helpers/math_random.c\
			$(SRC_DIR)/helpers/csfml_utils.c\

CFLAGS	=		-I $(ROOT)/inc $(EFLAGS)

LFLAGS	=		-lm  -l csfml-graphics -l csfml-window -l csfml-system -l csfml-audio #-L $(ROOT)/../lib/my -lmy #-fsanitize=address

EFLAGS	=		-Wall -Wextra -Wpedantic -g3

LIB 	=		../lib/%.a

DEBUG_FLAG	=	--no-print-directory

V		=		@

OBJS	=		$(patsubst $(SRC_DIR)/%.c, $(REAL)/%.o, $(SRC))

#COLOR
WHITE	=			\e[0m
DARK_RED	= 		\e[38;5;160m
RED		=			\e[38;5;203m
GREEN	=			\e[1;32m
ORANGE	=			\e[1;33m
BLUE	=			\e[38;5;21m
PURPLE 	= 			\e[38;5;63m
CYAN 	=			\e[38;5;51m
PINK 	= 			\e[38;5;162m
LIGHT_PURPLE = 		\e[38;5;147m
DARK_BLUE	= 		\e[38;5;26m
BOLD	=			\e[1m

all:		intro $(NAME)

intro:
	$(V) printf "$(DARK_RED)$(BOLD)+------------------------------+\n$(WHITE)"
	$(V) printf "$(DARK_RED)$(BOLD)|        SIMULATION V0.1       |\n$(WHITE)"
	$(V) printf "$(DARK_RED)$(BOLD)+------------------------------+\n\n$(WHITE)"

$(NAME): $(REAL)/$(NAME)
	$(V) cp $(REAL)/$(NAME) $(ROOT)
	$(V) printf "$(RED)\nDup $(RED)$(BOLD)$(NAME)$(WHITE)$(RED) into root directory.$(WHITE)\n"
	$(V) printf "$(ORANGE)Project compilation success\n$(WHITE)"

#../lib/libmy.a
$(REAL)/$(NAME):		$(OBJS)
	$(V) printf "$(ORANGE)[OK]$(BOLD)$(DARK_BLUE) Linking obj and libraries.$(WHITE)\n"
	$(V) $(CC) -o $(REAL)/$(NAME) $(OBJS) $(LFLAGS)
	$(V) printf "$(ORANGE)[OK]$(BOLD)$(DARK_BLUE) Binary link done.$(WHITE)\n"

$(REAL)/%.o: $(SRC_DIR)/%.c | $(REAL)
	$(V) mkdir -p $(dir $@)
	$(V) printf "$(DARK_BLUE)Compiling $(GREEN)$(DARK_BLUE)[$(WHITE)$(DARK_BLUE)$(notdir $<)$(GREEN)$(DARK_BLUE) -> $(CYAN)$(notdir $@)$(GREEN)$(DARK_BLUE)]\n$(WHITE)"
	$(V) $(CC) -o $@ -c $< $(CFLAGS) $(LFLAGS)

../lib/lib%.a:
	$(V) $(MAKE) -C ../lib/$* $(DEBUG_FLAG)

$(REAL):
	$(V) mkdir $@

clean:
	$(V) rm -rf $(OBJS)
	$(V) printf "$(RED)Removing object files.$(WHITE)\n"

fclean:	clean
	$(V) rm -f $(REAL)/$(NAME)
	$(V) rm -f $(ROOT)/$(NAME)
	$(V) rm -rf $(REAL)
	$(V) rm -rf $(ROOT)/champions/*.cor
	$(V) rm -rf $(ROOT)/champions/test/*.cor
	$(V) printf "$(RED)Removing binary file.$(WHITE)\n"

re:	fclean
	$(V) make --no-print-directory all

.PHONY: clean fclean debug all re intro

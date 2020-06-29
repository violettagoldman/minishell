NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 -Ofast -flto -march=native -Iinc/

TOTAL = $(shell find src -iname  "*.c" | wc -l | bc)
O_COUNT = 0
COUNT = 0

define update
	$(eval O_COUNT := $(shell find obj -iname "*.o" 2> /dev/null | wc -l | bc))
	printf "\r["
	printf '=%.0s' {0..${O_COUNT}}
	printf ">"
	$(eval COUNT := $(shell echo ${TOTAL} - ${O_COUNT} | bc))
	printf "%${COUNT}s" "]"
endef

ifeq ($(D), 1)
    CFLAGS += -fsanitize=address
endif
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	TICK = \342\234\224
	CC = clang
else
	TICK = \xE2\x9C\x94
	CC = gcc
endif

SRC_DIR = ./src/
SRC = ${wildcard src/*.c}
SRC_GNL = ${wildcard src/get_next_line/*.c}
SRC_PRINTF = ${wildcard src/ft_printf/*.c}
OBJ = ${patsubst src/%.c, obj/%.o, ${SRC}}
OBJ_GNL = ${patsubst src/get_next_line/%.c, obj/get_next_line/%.o, ${SRC_GNL}}
OBJ_PRINTF = ${patsubst src/ft_printf/%.c, obj/ft_printf/%.o, ${SRC_PRINTF}}

all: $(NAME)

$(NAME): ${OBJ} ${OBJ_GNL} ${OBJ_PRINTF}
	@${CC} ${OBJ} ${OBJ_GNL} ${OBJ_PRINTF} ${CFLAGS} -o ${NAME}
	@echo "\033[32;1m\rminishell by Violetta Goldman and Tom Marx is done ${TICK}          \033[0m"

./obj/get_next_line/%.o: ./src/get_next_line/%.c
	@mkdir -p ./obj/get_next_line
	@${CC} ${CFLAGS} -c $< -o $@
	@$(call update)

./obj/ft_printf/%.o: ./src/ft_printf/%.c
	@mkdir -p ./obj/ft_printf
	@${CC} ${CFLAGS} -c $< -o $@
	@$(call update)

./obj/%.o: ./src/%.c
	@mkdir -p ./obj
	@${CC} ${CFLAGS} -c $< -o $@
	@$(call update)

run: ${NAME}
	@./${NAME}

norme:
	@norminette ${SRC_DIR}

clean:
	@rm -rf obj
	@echo "\033[32;1mCleaned minishell ${TICK}\033[0m"

fclean:	clean
	@rm -rf ${NAME} minishell.dySM
	@echo "\033[32;1mForced cleaned minishell ${TICK}\033[0m"

re:	fclean all

.PHONY: clean fclean all re

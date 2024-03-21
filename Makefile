# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 17:21:47 by chmoussa          #+#    #+#              #
#    Updated: 2024/02/08 17:21:47 by chmoussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPTINAME = mygame_opti
NAME 	= demineur
INCLUDE = -I include
SRC_DIR = src
SRCS = main.c itoa.c event.c draw.c utils.c animation_logic.c core.c mouse_checks.c
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
SRC = $(addprefix $(SRC_DIR)/,$(SRCS))
FSAN = -fsanitize=address
DEBUG = -g3 -O0
OPTI = -O3
CC = cc
#LIB = $(shell pkg-config --libs --cflags raylib)

UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
	CFLAGS += -D LINUX
	LIB_INCL =
	LIB_DIR = -lraylib
endif
ifeq ($(UNAME),Darwin)
	CFLAGS += -D MAC
	LIB_INCL = -I mac
	LIB_DIR = -L mac -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
endif

FLAGS = -Wall -Wextra -Werror
BUILD_DIR = build

all: build_dir $(NAME)

val: $(NAME)
	$(CC) $(INCLUDE) $(DEBUG) $^ $(LIB_INCL) $(LIB_DIR) -o $(NAME)

opti: $(OBJ)
	$(CC) $(INCLUDE) $(FLAGS) $(OPTI) $^ $(LIB_INCL) $(LIB_DIR) -o $(OPTINAME)

build_dir:
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@ $(INCLUDE) $(LIB_INCL)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) $(FSAN) $(OBJ) -o $(NAME) $(LIB_DIR) 

clean:
	rm -rf build/

fclean: clean
	rm -f demineur
	rm -rf demineur.*

re: fclean all

fc: fclean

.PHONY: fclean fc clean all val opti

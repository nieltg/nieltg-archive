# Makefile by @nieltg

# Places

OUT_DIR := bin
OBJ_DIR := $(OUT_DIR)/obj

SRC_DIR := src

SRC_DIRS := $(shell find src -type d)
SRC_OBJS := $(shell find src -name '*.c' -type f)

OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS))
OBJ_OBJS := $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(SRC_OBJS)))

# Tools

CC_ARG_PRE := -Wall $(if $(DEBUG),-ggdb,)
CC_ARG_POS := -I$(SRC_DIR)

LD := gcc $(CC_ARG_PRE)
CC := gcc $(CC_ARG_PRE) -std=gnu99 -c

# Targets

APP := main

.PHONY: all clean

all: $(OUT_DIR)/$(APP)

$(OUT_DIR)/$(APP): $(OBJ_OBJS) | $(OUT_DIR)
	@echo " link: $@"
	@$(LD) -o $@ $^

$(OUT_DIR) $(OBJ_DIRS):
	@echo " mkdir: $@"
	@mkdir -p $@

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIRS)
	@echo " cc: $@"
	@$(CC) -o $@ $< $(CC_ARG_POS)

clean:
	@echo " cleanup: $(OUT_DIR)"
	@rm -r $(OUT_DIR)

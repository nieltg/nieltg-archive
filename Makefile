# Makefile by @nieltg

# Places

OUT_DIR := bin
OBJ_DIR := $(OUT_DIR)/obj
DRI_DIR := $(OUT_DIR)/test

SRC_DIR := src
SRC_DRI_DIR := test

SRC_DIRS := $(shell find $(SRC_DIR) -type d 2> /dev/null)
SRC_DRI_DIRS := $(shell find $(SRC_DRI_DIR) -type d 2> /dev/null)

SRC_OBJS := $(shell find $(SRC_DIR) -name '*.cpp' -type f 2> /dev/null)
SRC_DEFS := $(shell find $(SRC_DIR) -name '*.h' -type f 2> /dev/null)

OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS) $(SRC_DRI_DIRS))
OBJ_OBJS := $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(SRC_OBJS)))

ifdef DRI_CUR
DRI_SRCS := $(shell find $(DRI_CUR) -name '*.cpp' -type f 2> /dev/null)
DRI_DEFS := $(shell find $(DRI_CUR) -name '*.h' -type f 2> /dev/null)
DRI_OBJS := $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(DRI_SRCS)))

DRI_OBJ_OBJS := \
	$(foreach obj,$(OBJ_OBJS),$(shell nm $(obj) | grep -q -w main || echo $(obj)))
endif

# Tools

CC_ARG_PRE := -Wall $(if $(DEBUG),-ggdb,-Ofast)
CC_ARG_POS := -I$(SRC_DIR)

LD := clang++ $(CC_ARG_PRE)
CC := clang++ $(CC_ARG_PRE) -std=c++11 -c

# Targets

APP := main

.PHONY: all clean dri_helper

all: $(OUT_DIR)/$(APP)

FORCE: ;

$(OUT_DIR)/$(APP): $(OBJ_OBJS)
	@echo " link: $@"
	@$(LD) -o $@ $^

$(OUT_DIR) $(OBJ_DIRS) $(DRI_DIR):
	@echo " mkdir: $@"
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.cpp $(SRC_DEFS) | $(OBJ_DIRS)
	@echo " cc: $@"
	@$(CC) -o $@ $< $(CC_ARG_POS)

dri_helper: $(DRI_OUT)

$(DRI_OUT): $(DRI_OBJS) $(DRI_OBJ_OBJS) | $(DRI_DIR)
	@echo " link: $@"
	@$(LD) -o $@ $^

$(DRI_DIR)/%: $(SRC_DRI_DIR)/% $(OBJ_OBJS) FORCE | $(OBJ_DIRS)
	@echo " make: $@"
	@$(MAKE) --no-print-directory dri_helper DRI_OUT=$@ DRI_CUR=$<

clean:
	@echo " cleanup: $(OUT_DIR)"
	@rm -rf $(OUT_DIR)

# NIM/Nama  : 13515071 / Daniel Pintara
# Tanggal   : Fri Sep 9, 2016
# Topik     : DFA
# Deskripsi : Implementasi DFA pada vending machine sederhana

# Places

OUT_DIR := bin
OBJ_DIR := $(OUT_DIR)/obj

SRC_DIR := src

OBJS := $(addprefix $(OBJ_DIR)/, common.o dfa.o main.o parse.o)

# Tools

LD := gcc
CC := gcc -std=gnu99 -c

APP := dfaexec

.PHONY: all clean

all: $(OUT_DIR)/$(APP)

$(OUT_DIR)/$(APP): $(OBJS) | $(OUT_DIR)
	@echo " link: $@"
	@$(LD) -o $@ $^

$(OBJ_DIR): | $(OUT_DIR)
	@echo " mkdir: $@"
	@mkdir -p $@

$(OUT_DIR):
	@echo " mkdir: $@"
	@mkdir -p $@

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo " cc: $@"
	@$(CC) -o $@ $<

clean:
	@echo " cleanup: $(OUT_DIR)"
	@rm -r $(OUT_DIR)


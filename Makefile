# =========================
# ПАРАМЕТРЫ ЗАПУСКА
# =========================
STAGE ?= stage0
MODE  ?= oop

ROOT := $(CURDIR)
TARGET_DIR := stages/$(STAGE)/$(MODE)
SRC_DIR := $(TARGET_DIR)/src
BUILD_DIR := $(TARGET_DIR)/build
BIN := $(BUILD_DIR)/app.out

# =========================
# OOP (C++)
# =========================
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

CPP_SRC := $(shell find $(SRC_DIR) -name '*.cpp')

# =========================
# PPP (ppclang через Docker)
# =========================
PPC_IMAGE := ppclang-legacy-ready

DOCKER := docker run --rm \
	--platform linux/amd64 \
	-v $(ROOT):/work \
	-w /work \
	$(PPC_IMAGE)

# Подхватить .bashrc
PPCLANG := $(DOCKER) bash -i -c "ppclang"

PPC_SRC := $(shell find $(SRC_DIR) -name 'main.c')

# =========================
# ОБЩИЕ ЦЕЛИ
# =========================
.PHONY: all build run clean info

all: build

# =========================
# СБОРКА
# =========================
build:
ifeq ($(MODE),oop)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CPP_SRC) -o $(BIN) $(CXXFLAGS)
else ifeq ($(MODE),ppp)
	@mkdir -p $(BUILD_DIR)
	$(DOCKER) bash -i -c "ppclang $(PPC_SRC) -o $(BIN)"
else
	$(error MODE must be oop or ppp)
endif

# =========================
# ЗАПУСК
# =========================
run: build
ifeq ($(MODE),oop)
	./$(BIN)
else ifeq ($(MODE),ppp)
	$(DOCKER) bash -i -c "./$(BIN)"
endif

# =========================
# СЛУЖЕБНОЕ
# =========================
clean:
	rm -rf $(BUILD_DIR)

info:
	@echo "Stage : $(STAGE)"
	@echo "Mode  : $(MODE)"
	@echo "Src   : $(SRC_DIR)"
	@echo "Bin   : $(BIN)"


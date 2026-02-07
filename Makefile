# =========================
# ПАРАМЕТРЫ ЗАПУСКА
# =========================
STAGE ?= stage0
MODE  ?= oop
USE_DOCKER ?= yes

ROOT := $(CURDIR)
TARGET_DIR := stages/$(STAGE)/$(MODE)
SRC_DIR := $(TARGET_DIR)/src
BUILD_DIR := $(TARGET_DIR)/build
BIN := $(BUILD_DIR)/app.out

# =========================
# PPP Containers
# =========================
PPSCL_DIR := libs/ppscl
PPSCL_SOURCES := $(shell find $(PPSCL_DIR) -name '*.c')
PPSCL_INCLUDE := $(addprefix -I,$(shell find $(PPSCL_DIR) -type d))

# =========================
# OOP (C++)
# =========================
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

CPP_SRC := $(shell find $(SRC_DIR) -name '*.cpp')

# =========================
# PPClang
# =========================
ifeq ($(USE_DOCKER),yes)
    PPC_IMAGE := ppclang-slim
    DOCKER := docker run --rm -it \
        --platform linux/amd64 \
        -v $(ROOT):/work \
        -w /work \
        $(PPC_IMAGE)
    PPCLANG := $(DOCKER) bash -i -c "ppclang"
else
    PPCLANG := ppclang
endif

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
ifeq ($(USE_DOCKER),yes)
	$(DOCKER) bash -i -c "ppclang $(PPC_SRC) $(PPSCL_SOURCES) $(PPSCL_INCLUDE) -o $(BIN)"
else
	ppclang $(PPC_SRC) $(PPSCL_SOURCES) $(PPSCL_INCLUDE) -o $(BIN)
endif
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
ifeq ($(USE_DOCKER),yes)
	$(DOCKER) bash -i -c "./$(BIN)"
else
	./$(BIN)
endif
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


# ------------ CONFIG ---------------
CXX       	:= g++
CXXFLAGS  	:= -std=c++17 -Wall -Wextra -pedantic

BREW_PREFIX := $(shell command -v brew >/dev/null 2>&1 && brew --prefix || echo "")
INCLUDES    := -Iinclude $(if $(BREW_PREFIX),-I$(BREW_PREFIX)/include)
LIBS        := $(if $(BREW_PREFIX),-L$(BREW_PREFIX)/lib) -lunistring

BUILD_DIR	:= build

SRC       	:= src/main.cpp
TARGET		:= strui
BIN       	?= $(BUILD_DIR)/$(TARGET)
INSTALL_DIR := $(HOME)/.local/bin

# ------------ RULES ----------------

all: clean $(BIN)

$(BUILD_DIR):
	@echo "----------------"
	@echo "⚙️  \033[38;5;208mCompiling...\033[0m"
	@echo "----------------"
	mkdir -p $(BUILD_DIR)

$(BIN): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@ $(LIBS)
	@echo "\033[32m✔\033[0m Built: $@"

install: all
	@echo "----------------"
	@echo "🛠️  \033[38;5;208mInstalling...\033[0m"
	@echo "----------------"
	mkdir -p $(INSTALL_DIR)
	cp $(BIN) $(INSTALL_DIR)/$(TARGET)
	@echo "\033[32m✔\033[0m Installed to $(INSTALL_DIR)/$(TARGET)"
	@echo "$$PATH" | grep -q "$(INSTALL_DIR)" || echo "⚠️  Warning: $(INSTALL_DIR) is not in your PATH"

test: install
	@sh tests/run.sh

clean:
	@echo "----------------"
	@echo "🧹 \033[38;5;208mCleaning...\033[0m"
	@echo "----------------"
	[ -d $(BUILD_DIR) ] && rm -rf $(BUILD_DIR)

.PHONY: all test clean install


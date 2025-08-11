# muShell Makefile

# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE
DEBUG_FLAGS = -g -DDEBUG -fsanitize=address
RELEASE_FLAGS = -O2 -DNDEBUG

# Directories
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release
TEST_BUILD_DIR = $(BUILD_DIR)/tests

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEBUG_OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(DEBUG_DIR)/%.o)
RELEASE_OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(RELEASE_DIR)/%.o)

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c) $(wildcard $(TEST_DIR)/*/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(TEST_BUILD_DIR)/%.o)

# Executables
TARGET = muShell
DEBUG_TARGET = $(DEBUG_DIR)/$(TARGET)
RELEASE_TARGET = $(RELEASE_DIR)/$(TARGET)
TEST_TARGET = $(TEST_BUILD_DIR)/test_runner

# Include paths
INCLUDES = -I$(INC_DIR)

# Default target
all: release

# Release build
release: $(RELEASE_TARGET)

$(RELEASE_TARGET): $(RELEASE_OBJECTS) | $(RELEASE_DIR)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCLUDES) $^ -o $@

$(RELEASE_DIR)/%.o: $(SRC_DIR)/%.c | $(RELEASE_DIR)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCLUDES) -c $< -o $@

# Debug build
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJECTS) | $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) $^ -o $@

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c | $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -c $< -o $@

# Test build (for now, just create the structure)
test: $(TEST_TARGET)
	@echo "Running tests..."
	@echo "Test framework not yet implemented"

$(TEST_TARGET): $(TEST_OBJECTS) | $(TEST_BUILD_DIR)
	@echo "Test target created (placeholder)"

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -c $< -o $@

# Create directories
$(DEBUG_DIR):
	mkdir -p $(DEBUG_DIR)

$(RELEASE_DIR):
	mkdir -p $(RELEASE_DIR)

$(TEST_BUILD_DIR):
	mkdir -p $(TEST_BUILD_DIR)

# Clean targets
clean:
	rm -rf $(BUILD_DIR)

clean-debug:
	rm -rf $(DEBUG_DIR)

clean-release:
	rm -rf $(RELEASE_DIR)

clean-tests:
	rm -rf $(TEST_BUILD_DIR)

# Install (copy to /usr/local/bin)
install: release
	sudo cp $(RELEASE_TARGET) /usr/local/bin/$(TARGET)

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Run targets
run: release
	./$(RELEASE_TARGET)

run-debug: debug
	./$(DEBUG_TARGET)

# Memory check with valgrind
memcheck: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(DEBUG_TARGET)

# Help target
help:
	@echo "muShell Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  all           - Build release version (default)"
	@echo "  release       - Build optimized release version"
	@echo "  debug         - Build debug version with symbols"
	@echo "  test          - Build and run tests"
	@echo "  clean         - Remove all build files"
	@echo "  clean-debug   - Remove debug build files"
	@echo "  clean-release - Remove release build files"
	@echo "  clean-tests   - Remove test build files"
	@echo "  install       - Install to /usr/local/bin"
	@echo "  uninstall     - Remove from /usr/local/bin"
	@echo "  run           - Build and run release version"
	@echo "  run-debug     - Build and run debug version"
	@echo "  memcheck      - Run with valgrind memory checking"
	@echo "  help          - Show this help message"

# Phony targets
.PHONY: all release debug test clean clean-debug clean-release clean-tests install uninstall run run-debug memcheck help

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -Iinclude
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2
LDFLAGS = 
OBJ = blockchain.o block.o hash.o network.o main.o
TARGET = blockchain

# Default target: Release mode
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: clean $(TARGET)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean debug release run

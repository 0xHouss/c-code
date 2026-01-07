# Compiler and flags
CC = gcc
CFLAGS = -fPIC -Wall -O2
LDFLAGS = -shared

# Project files
SRC = src/stack.c
OBJ = $(SRC:.c=.o)
TARGET = libstack.so
PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib

# Default target: build the shared library
all: $(TARGET)

# Build shared library
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Install library and header
install: $(TARGET)
	@echo "Installing library to $(LIB_DIR) and header to $(INCLUDE_DIR)..."
	install -d $(LIB_DIR) $(INCLUDE_DIR)
	install -m 644 $(TARGET) $(LIB_DIR)
	install -m 644 include/stack.h $(INCLUDE_DIR)
	sudo ldconfig
	@echo "Installed successfully."

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all install clean


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Project files
SRC = main.c rterm.c listc.c keyb.c opfile.c global.c fileb.c viewer.c
OBJ = main.o rterm.o listc.o keyb.o opfile.o global.o fileb.o viewer.o
EXEC = fread

# Build target
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean


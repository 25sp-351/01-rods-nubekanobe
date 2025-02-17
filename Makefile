# Makefile

# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -g

# Executable name
TARGET = rods

# Object files
OBJS = rods.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile source files to object files
rods.o: rods.c
	$(CC) $(CFLAGS) -c rods.c -o rods.o

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)


# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Sources and object files
SRCS = HW5MainFile.c 
OBJS = $(SRCS:.c=.o)

# Executable file name
TARGET = HW5program

# The default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
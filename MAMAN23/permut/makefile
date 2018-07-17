# Global definitions
CC = gcc 
CPPFLAGS = -g -Wall -ansi -pedantic  
# Directory structure
INC_DIR = ./
CPPFLAGS += -I$(INC_DIR)

# all contents of current directory
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
# Target and sources
TARGET = permut

# Dependencies

all: $(TARGET)

$(TARGET): $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.c) > depends


clean:
	-rm -f *.o
	-rm -f permut
	-rm -f depends


run: all
	./permut

gdb: all
	gdb ./permut



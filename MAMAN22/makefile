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
TARGET = myset

# Dependencies

all: $(TARGET)

$(TARGET): $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.c) > depends


clean:
	-rm -f *.o
	-rm -f myset
	-rm -f depends


run: all
	./myset

gdb: all
	gdb ./myset



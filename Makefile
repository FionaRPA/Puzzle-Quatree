TARGET = main
CFLAGS =`pkg-config --cflags MLV` quadTree.c quad.c puzzle.c
LDLIBS = `pkg-config --libs MLV`

all: $(TARGET)

clean:
	-rm -rf $(TARGET)

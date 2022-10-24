TARGET=test-list-modules
MODULE=list-modules.o
LIB=liblist.a
CFLAGS=-std=c89 -pedantic

$(TARGET): $(LIB)
	gcc $(MODULE) $(TARGET).c -o $(TARGET)

$(LIB): $(MODULE)
	ar -crs $(LIB) $(MODULE)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clear:
	rm -f *.o $(TARGET) *~
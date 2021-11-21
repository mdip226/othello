CC = g++
CFLAGS = -Wall
OBJS = main.o debug.o moves.o actions.o utils.o minmax.o
TARGET = mdippelOthello

all: $(TARGET)
	g++ -o $(TARGET) main.o debug.o moves.o actions.o utils.o minmax.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test: test.o debug.o moves.o actions.o utils.o minmax.o
	g++ -o test test.o debug.o moves.o actions.o utils.o minmax.o

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f $(OBJS) test.o

clean_all:
	rm -f $(TARGET)
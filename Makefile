CC = g++
CFLAGS = -Wall
OBJS = main.o debug.o moves.o actions.o utils.o
TARGET = othello

all: $(TARGET)
	g++ -o othello main.o debug.o moves.o actions.o utils.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test: test.o debug.o moves.o actions.o utils.o
	g++ -o test test.o debug.o moves.o actions.o utils.o

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f $(OBJS)

clean_all:
	rm -f $(TARGET)
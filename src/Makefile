CC=g++
CFLAGS=-Wall -std=c++11 -g -DDEBUG_H
TARGET=main
FILES=main.o utils.o WFEHashMap.o Node.o DataNode.o ArrayNode.o

%: all

all: $(TARGET)

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o $(TARGET)

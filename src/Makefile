CC=g++
CFLAGS=-Wall -std=c++11 -pthread -g
TARGET=main
FILES=main.o utils.o WFEHashMap.o LBEHashMap.o Node.o DataNode.o ArrayNode.o

%: all

all: $(TARGET)

debug: CFLAGS += -DDEBUG_H
debug: all

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o $(TARGET)

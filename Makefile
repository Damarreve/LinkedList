CC=g++
RM=rm -rf
CFLAGS=-c
CXXFLAGS=-Iinclude/
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=LinkedList

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CXXFLAGS)
	$(RM) $(OBJECTS)

$(OBJECTS): $(SOURCES)

clean:
	$(RM) $(OBJECTS) $(TARGET)

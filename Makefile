CXXFLAGS=-Iinclude/
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=LinkedList
RM=rm -rf

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)
	$(RM) $(OBJECTS)

$(OBJECTS): $(SOURCES)

clean:
	$(RM) $(OBJECTS) $(TARGET)

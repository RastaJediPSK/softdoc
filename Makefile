TARGET = main

CXX = g++

# CPPFLAGS are for all languages (C and C++)
CPPFLAGS = -Iinclude
CPPFLAGS += -Wall
CPPFLAGS += -Wextra

# CXXFLAGS are just for C++
CXXFLAGS = -Weffc++

# CFLAGS are just for C

# linking flags
LDFLAGS = 

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=bin/%.o)

all: bin/$(TARGET)

#bin/$(TARGET): $(OBJECTS)
#	echo "OBJECTS: $(OBJECTS)"
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) bin/$< -o $@

#src/%.cpp:

src/%.cpp: bin/%.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) bin/$< -o $@

bin/%.o: src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

#all: main unit 

#main: main.o unit.o
	$(CXX) $(CPPFLAGS) -o main main.o unit.o

#bin/%: src/%.cpp
#	$(CXX) $(CPPFLAGS) -o $@ src/common.cpp $< $(LDFLAGS)

.PHONY: all clean

clean:
	rm -rf bin/*

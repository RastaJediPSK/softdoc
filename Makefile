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

bin/$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

bin/%.o: src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	rm -rf bin/*

.PHONY: all clean

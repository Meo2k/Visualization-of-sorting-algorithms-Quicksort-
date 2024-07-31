# Name the executable file
TARGET = new

# Đặt đường dẫn
SRCDIR = ../src
INCDIR = $(SRCDIR)/include
LIBDIR = $(SRCDIR)/lib
NEWDIR = .

# Source code files and objects
SOURCES = $(NEWDIR)/quicksort.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Select compiler
CXX = g++
CXXFLAGS = -std=c++11 -I$(INCDIR)
LDFLAGS = -L$(LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Default target
all: $(TARGET)

# Rules for creating executable files
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Rules for compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning rules
clean:
	rm -f $(OBJECTS) $(TARGET)

# The goal is to compile and run the program
run: $(TARGET)
	./$(TARGET)

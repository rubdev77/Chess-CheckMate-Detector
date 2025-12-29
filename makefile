# Define the compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Define the source files and the executable name
SRCS = main.cpp Pieces.cpp Piece.cpp
TARGET = exe

# Rule to build the target executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean rule to delete object files and the executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
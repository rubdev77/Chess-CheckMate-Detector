# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Target executable name
TARGET = chess_game

# Source files (All your .cpp files)
SRCS = main.cpp Piece.cpp Pieces.cpp

# Object files (Generated from .cpp files)
OBJS = $(SRCS:.cpp=.o)

# Header files (For dependency tracking)
DEPS = Matrix.h ChessBoard.h Piece.h Pieces.h

# Default rule: build the target
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
# It depends on the headers, so if a header changes, the .cpp re-compiles
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program
run: all
	./$(TARGET)
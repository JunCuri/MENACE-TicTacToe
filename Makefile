CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/board.cpp src/matchbox.cpp
OBJ = $(SRC:.cpp=.o)

train: $(OBJ) main/train.cpp
	$(CXX) $(CXXFLAGS) -o train $(OBJ) main/train.cpp

play: $(OBJ) main/play.cpp
	$(CXX) $(CXXFLAGS) -o play $(OBJ) main/play.cpp

clean:
	rm -f $(OBJ) train play
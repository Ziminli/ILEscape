CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb -static-libgcc -static-libstdc++

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := lib -l sfml-graphics -l sfml-window -l sfml-system
EXECUTABLE  := ILEscape


all: $(BIN)/$(EXECUTABLE)

run:
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $(BIN)/$(EXECUTABLE) -L $(LIBRARIES)

clean:
	-rm $(BIN)/*
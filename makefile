CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include/SDL2 -Iinclude
LDFLAGS  = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_mixer
SRC = src/*.cpp
TARGET = shooting_game

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

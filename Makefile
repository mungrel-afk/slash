CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS  = -Llib
LIBS     = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 
SRC      = $(wildcard src/*.cpp)
TARGET   = Slash

run: build
	./$(TARGET)

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)


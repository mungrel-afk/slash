CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC      = $(wildcard src/*.cpp)

ifeq ($(OS),Windows_NT)
    TARGET  = Slash.exe
    LDFLAGS = -Llib/windows
    LIBS    = -lraylib -lopengl32 -lgdi32 -lwinmm
    RUN     = "$(CURDIR)/$(TARGET)"
    RM      = powershell -NoProfile -Command Remove-Item -Force
else
    TARGET  = Slash
    LDFLAGS = -Llib/linux
    LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    RUN     = ./$(TARGET)
    RM      = rm -f
endif

.PHONY: run build clean

run: build
	$(RUN)

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LIBS)

clean:
	$(if $(wildcard $(TARGET)),$(RM) $(TARGET))

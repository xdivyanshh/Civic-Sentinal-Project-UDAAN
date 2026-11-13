CXX = g++
CXXFLAGS = -std=c++14 -O2 -static -static-libgcc -static-libstdc++ -Iinclude
TARGET = udaan_engine
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) --bridge

demo: $(TARGET)
	./$(TARGET) --demo

clean:
	rm -f $(TARGET) $(TARGET).exe

CXX = g++
CXXFLAGS = -Wall -std=c++11 -Isrc

SD = src
TD = test
BD = build


SOURCES = $(SD)/point.cpp $(SD)/circle.cpp $(SD)/list.cpp
OBJECTS = $(BD)/point.o $(BD)/circle.o $(BD)/list.o
TEST_SOURCE = $(TD)/test.cpp
TARGET = $(BD)/test_app

all: prepare $(TARGET)

prepare:
	mkdir -p $(BD)

$(TARGET): $(OBJECTS) $(BD)/test.o
	$(CXX) $(OBJECTS) $(BD)/test.o -o $(TARGET)

$(BD)/%.o: $(SD)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BD)/test.o: $(TEST_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(TEST_SOURCE) -o $(BD)/test.o

clean:
	rm -rf $(BD) *.txt

run: all
	./$(TARGET)
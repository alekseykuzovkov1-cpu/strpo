CXX      = g++
CXXFLAGS = -g -Wall -std=c++17 -I./src

SRC_DIR   = src
BUILD_DIR = build
TEST_DIR  = test

SRCS = $(filter-out $(SRC_DIR)/lab3.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET      = $(BUILD_DIR)/lab3
TEST_TARGET = $(BUILD_DIR)/run_tests


all: $(TARGET)

$(TARGET): $(BUILD_DIR)/lab3.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(BUILD_DIR)/test_priority.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


$(BUILD_DIR)/lab3.o: $(SRC_DIR)/lab3.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_priority.o: $(TEST_DIR)/test_priority.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

leak: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test clean leak
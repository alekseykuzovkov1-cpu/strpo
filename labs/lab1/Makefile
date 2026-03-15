# компилятор и флаги
# улучшение: можно переопределить (make CXX=clang++)
CXX      ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra
DEBUGFLAGS = -g -O0

# флаги для проверки утечек памяти
LEAKFLAGS = -g -fsanitize=address -fno-omit-frame-pointer

# директории
SRC_DIR   = src
TEST_DIR  = tests
BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
TARGET    = $(BUILD_DIR)/debug.out

# целевой файл для проверки утечек
LEAK_TARGET = $(BUILD_DIR)/leaks.out

# улучшение: автоматический поиск всех .cpp файлов в src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# 4.1.

# тестовые файлы
TEST_RECT_SRC = $(TEST_DIR)/test_rect_basic_methods.cpp
TEST_RECT_TARGET = $(BUILD_DIR)/test_rect_basic_methods.out

$(TEST_RECT_TARGET): $(TEST_RECT_SRC) $(SRC_DIR)/rect.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(TEST_RECT_SRC) $(SRC_DIR)/rect.cpp -o $@
	@echo "Тест собран: $@"

test-rect: $(TEST_RECT_TARGET)
	@./$(TEST_RECT_TARGET)

# 4.2

# тест свойств
TEST_PROPERTIES_TARGET = $(BUILD_DIR)/test_rect_properties.out
$(TEST_PROPERTIES_TARGET): tests/test_rect_properties.cpp src/rect.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $^ -o $@

test-properties: $(TEST_PROPERTIES_TARGET)
	./$(TEST_PROPERTIES_TARGET)

# тест операций
TEST_OPERATIONS_TARGET = $(BUILD_DIR)/test_rect_operations.out
$(TEST_OPERATIONS_TARGET): tests/test_rect_operations.cpp src/rect.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $^ -o $@

test-operations: $(TEST_OPERATIONS_TARGET)
	./$(TEST_OPERATIONS_TARGET)

# тест bounding_rect
TEST_BOUNDING_TARGET = $(BUILD_DIR)/test_bounding_rect.out
$(TEST_BOUNDING_TARGET): tests/test_bounding_rect.cpp src/rect.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $^ -o $@

test-bounding: $(TEST_BOUNDING_TARGET)
	./$(TEST_BOUNDING_TARGET)

#4.3

test: test-rect test-properties test-operations test-bounding
	@echo "Все тесты пройдены!"

# улучшение: автоматическая генерация зависимостей от .hpp файлов
CPPFLAGS = -MMD -MP
DEPENDS  = $(patsubst $(OBJ_DIR)/%.o, $(OBJ_DIR)/%.d, $(OBJECTS))

# TODO: узнать, что это, как работает, в каких сборках Make доступно
-include $(DEPENDS)
# подключает файлы зависимостей .d, которые автоматически создает компилятор. В них записано, от каких заголовочных файлов .hpp зависит каждый .cpp файл. Доступно во всех современных версиях GNU Make

# создание директорий
$(OBJ_DIR) $(BUILD_DIR):
	mkdir -p $@

# улучшение: одно паттерн-правило для компиляции всех .cpp файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(CPPFLAGS) -c $< -o $@

# сборка исполняемого файла
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $^ -o $@

# сборка версии для проверки утечек памяти
$(LEAK_TARGET): $(SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LEAKFLAGS) $(SOURCES) -o $@

# цель для запуска проверки утечек с ручным вводом
leaks: $(LEAK_TARGET)
	./$(LEAK_TARGET)

# цели для запуска
run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb $(TARGET)

memcheck: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# улучшение: разные уровни очистки
clean:
	rm -rf $(OBJ_DIR)

distclean:
	rm -rf $(BUILD_DIR)

.PHONY: run debug memcheck
.PHONY: clean distclean
.PHONY: leaks
.PHONY: test-rect test-properties test-operations test-bounding

# цель по умолчанию
all: $(TARGET)
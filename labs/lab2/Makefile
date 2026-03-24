# Настройки компилятора
CXX = g++
CXXFLAGS = -Wall -I./src -g

# Папки
SRC_DIR = src
BUILD_DIR = build
FILES_DIR = src/files

# Поиск всех .cpp файлов в src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Превращаем пути .cpp в пути .o внутри build
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Имя исполняемого файла
TARGET = $(BUILD_DIR)/a.out

# Главная цель
all: prepare $(TARGET)

# --- ПРАВИЛО ПРЕДПОДГОТОВКИ (Его не хватало) ---
prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(FILES_DIR)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "--- Сборка завершена: $(TARGET) ---"

# Компиляция каждого .cpp в .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка проекта
clean:
	rm -rf $(BUILD_DIR)
	@echo "--- Папка build очищена ---"

# Запуск программы
run: all
	./$(TARGET)

.PHONY: all prepare clean run
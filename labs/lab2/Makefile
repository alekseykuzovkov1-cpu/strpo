CXX = g++
CXXFLAGS = -Wall -I./src -I./test -g

# папки
BD = build
SD = src
TD = test

# объектные файлы классов (из папки src)
LIB_OBJS = $(BD)/basefile.o \
       	$(BD)/mystring.o \
       	$(BD)/base32file.o \
       	$(BD)/base32file2.o \
       	$(BD)/rlefile.o \
       	$(BD)/rlefile2.o

# имена исполняемых файлов тестов
TEST_BINS = $(BD)/test_base $(BD)/test_b32 $(BD)/test_rle $(BD)/test_complex

# главная цель
all: prepare $(BD)/a.out

prepare:
	@mkdir -p $(BD)
	@mkdir -p src/files

# сборка основной программы
$(BD)/a.out: $(SD)/lab2.cpp $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# компиляция объектов классов из src
$(BD)/%.o: $(SD)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# компиляция утилит теста (test_utils.cpp)
$(BD)/test_utils.o: $(TD)/test_utils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# сборка каждого конкретного теста
$(BD)/test_base: $(TD)/test_base.cpp $(BD)/test_utils.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BD)/test_b32: $(TD)/test_b32.cpp $(BD)/test_utils.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BD)/test_rle: $(TD)/test_rle.cpp $(BD)/test_utils.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BD)/test_complex: $(TD)/test_complex.cpp $(BD)/test_utils.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# цель для запуска тестов
test: prepare $(TEST_BINS)
	@echo "Запуск тестов"
	./$(BD)/test_base
	./$(BD)/test_b32
	./$(BD)/test_rle
	./$(BD)/test_complex

clean:
	rm -rf $(BD)

run: all
	./$(BD)/a.out

.PHONY: all prepare clean run test
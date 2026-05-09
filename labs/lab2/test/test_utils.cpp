#include "test_utils.hpp"
#include <cstdlib>
#include <ctime>

char* generate_data(size_t size) {
    char* data = new char[size];
    srand(time(0));
    
    for (size_t i = 0; i < size; i++) {
        data[i] = (char)(rand() % 256);
    }
    return data;
}

bool compare(const char* a, const char* b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}
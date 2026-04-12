#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <cstddef>

char* generate_data(size_t size);
bool compare(const char* a, const char* b, size_t size);

#endif
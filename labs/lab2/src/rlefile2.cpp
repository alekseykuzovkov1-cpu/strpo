#include "rlefile2.hpp"
#include <iostream>

using namespace std;

RleFile2::RleFile2(IFile* file) : target(file) {
    cout << "[CONSTRUCTOR] RleFile2 (Composition)" << endl;
}

RleFile2::~RleFile2() {
    cout << "[DESTRUCTOR] RleFile2 (Deleting target...)" << endl;
    delete target;
}

bool RleFile2::can_read() const { return target->can_read(); }
bool RleFile2::can_write() const { return target->can_write(); }

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    // Здесь ваша логика RLE
    // Вместо fwrite используем:
    // target->write(&count, 1); target->write(&symbol, 1);
    cout << "RleFile2: writing through target" << endl;
    return 0;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    return 0;
}
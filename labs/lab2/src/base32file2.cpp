#include "base32file2.hpp"
#include <cstring>
#include <iostream>

using namespace std;

Base32File2::Base32File2(IFile* file) : target(file) {
    strcpy(custom_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    init_decode_map();
    cout << "[CONSTRUCTOR] Base32File2 (Composition)" << endl;
}

Base32File2::~Base32File2() {
    cout << "[DESTRUCTOR] Base32File2 (Deleting target...)" << endl;
    delete target; // Ответственность за очистку по заданию
}

void Base32File2::init_decode_map() {
    memset(decode_map, 0, 256);
    for (int i = 0; i < 32; i++) {
        decode_map[(unsigned char)custom_table[i]] = i;
    }
}

bool Base32File2::can_read() const { return target->can_read(); }
bool Base32File2::can_write() const { return target->can_write(); }

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    // Здесь ваша логика кодирования Base32
    // Вместо fwrite используем:
    // return target->write(encoded_data, encoded_len);
    cout << "Base32File2: writing through target" << endl;
    return 0; 
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    cout << "Base32File2: reading through target" << endl;
    return 0;
}
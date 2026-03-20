#include "rlefile.hpp"
#include <iostream>
using namespace std;

// Конструктор по умолчанию
RleFile::RleFile() : BaseFile() {
    cout << "[CONSTRUCTOR] RleFile (default)" << endl;
}

// Конструктор с параметрами
RleFile::RleFile(const char* path, const char* mode) : BaseFile(path, mode) {
    cout << "[CONSTRUCTOR] RleFile (path: " << path << ")" << endl;
}

// Деструктор
RleFile::~RleFile() {
    cout << "[DESTRUCTOR] RleFile" << endl;
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!can_write() || n_bytes == 0) return 0;

    const unsigned char* data = (const unsigned char*)buf;
    size_t i = 0;
    size_t total_written_raw = 0;

    while (i < n_bytes) {
        unsigned char current_char = data[i];
        unsigned char count = 1;

        // Считаем одинаковые символы (макс. 255)
        while (i + 1 < n_bytes && data[i + 1] == current_char && count < 255) {
            count++;
            i++;
        }

        // Записываем пару: [счетчик][символ]
        total_written_raw += write_raw(&count, 1);
        total_written_raw += write_raw(&current_char, 1);
        i++;
    }

    return n_bytes; // Возвращаем количество обработанных исходных байт
}

size_t RleFile::read(void* buf, size_t max_bytes) {
    if (!can_read() || max_bytes == 0) return 0;

    unsigned char* out_buf = (unsigned char*)buf;
    size_t decoded_bytes = 0;

    while (decoded_bytes < max_bytes) {
        unsigned char count = 0;
        unsigned char value = 0;

        // Пытаемся считать счетчик
        if (read_raw(&count, 1) != 1) break;
        // Пытаемся считать значение
        if (read_raw(&value, 1) != 1) break;

        // Распаковываем, не выходя за границы буфера пользователя
        for (int j = 0; j < (int)count; ++j) {
            if (decoded_bytes < max_bytes) {
                out_buf[decoded_bytes++] = value;
            } else {
                // Если буфер кончился, а счетчик еще нет — это проблема 
                // простейшего RLE без внутреннего буфера.
                // В учебных целях считаем, что буфер достаточен.
                break; 
            }
        }
    }
    return decoded_bytes;
}
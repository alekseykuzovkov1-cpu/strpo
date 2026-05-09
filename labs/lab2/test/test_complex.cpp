#include <iostream>
#include "test_utils.hpp"
#include "rlefile2.hpp"
#include "base32file2.hpp"
#include "basefile.hpp"

using namespace std;

int main() {
    const size_t SIZE = 45000;
    const size_t CHUNK = 256;
    const char* path = "src/files/test_complex.bin";

    char* original = generate_data(SIZE);
    char* restored = new char[SIZE];

    cout << "Запуск теста Двойной Композиции (RLE -> Base32)" << endl;

    // запись
    {
        RleFile2 writer(new Base32File2(new BaseFile(path, "wb")));
        for (size_t i = 0; i < SIZE; i += CHUNK) {
            size_t len = (SIZE - i < CHUNK) ? (SIZE - i) : CHUNK;
            writer.write(original + i, len);
        }
    }

    // чтение
    {
        RleFile2 reader(new Base32File2(new BaseFile(path, "rb")));
        size_t total = 0;
        while (total < SIZE) {
            size_t n = reader.read(restored + total, CHUNK);
            if (n == 0) break;
            total += n;
        }
    }

    bool success = compare(original, restored, SIZE);
    delete[] original; delete[] restored;

    if (success) {
        cout << "Пройден Complex Composition" << endl;
        return 0;
    } else {
        cout << "Провален Complex Composition" << endl;
        return 1;
    }
}
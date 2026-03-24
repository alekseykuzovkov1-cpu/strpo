#ifndef BASE32FILE2_HPP
#define BASE32FILE2_HPP

#include "ifile.hpp"

class Base32File2 : public IFile {
private:
    IFile* target; // Объект, в который пойдет запись
    char custom_table[33];
    char decode_map[256];
    void init_decode_map();

public:
    Base32File2(IFile* file);
    ~Base32File2() override;

    bool can_read() const override;
    bool can_write() const override;
    size_t read(void* buf, size_t max_bytes) override;
    size_t write(const void* buf, size_t n_bytes) override;
};

#endif
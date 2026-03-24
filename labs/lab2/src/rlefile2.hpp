#ifndef RLEFILE2_HPP
#define RLEFILE2_HPP

#include "ifile.hpp"

class RleFile2 : public IFile {
private:
    IFile* target;

public:
    RleFile2(IFile* file);
    ~RleFile2() override;

    bool can_read() const override;
    bool can_write() const override;
    size_t read(void* buf, size_t max_bytes) override;
    size_t write(const void* buf, size_t n_bytes) override;
};

#endif
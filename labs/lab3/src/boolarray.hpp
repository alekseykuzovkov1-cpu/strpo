#ifndef BOOLARRAY_HPP
#define BOOLARRAY_HPP

#include <cstddef>
#include <cstdint> // для uint8_t

class BoolArray {
private:
    uint8_t* data_;
    size_t size_;
    size_t capacity_;

    static size_t bytes_needed(size_t bits) {
        return (bits + 7) / 8;
    }

    void set_bit(size_t index, bool value);
    bool get_bit(size_t index) const;

public:
    class BitProxy {
    private:
        BoolArray& array_;
        size_t index_;

    public:
        BitProxy(BoolArray& array, size_t index) : array_(array), index_(index) {}

        BitProxy& operator=(bool value) {
            array_.set_bit(index_, value);
            return *this;
        }

        BitProxy& operator=(const BitProxy& other) {
            array_.set_bit(index_, static_cast<bool>(other));
            return *this;
        }

        operator bool() const {
            return array_.get_bit(index_);
        }
    };

    BoolArray(size_t size, bool default_value = false);
    BoolArray(const BoolArray& other);
    ~BoolArray();

    BoolArray& operator=(const BoolArray& other);

    BitProxy operator[](size_t index);
    
    bool operator[](size_t index) const;

    size_t size() const { return size_; }
    void resize(size_t new_size, bool fill_value = false);
};

#endif
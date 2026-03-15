#include "basefile.hpp"

class Base32File : public BaseFile {
private:
    char encode_table_[33];           // таблица кодировки
    static int decode_table_[256];     // таблица декодировки (статическая для всех экземпляров)
    
    // внутренние буферы для последовательного кодирования/декодирования
    unsigned int bit_buffer_;          // буфер для накопления битов
    int bit_count_;                    // количество бит в буфере
    
    // инициализация таблицы декодировки
    void init_decode_table();
    
public:
    // конструкторы
    Base32File();
    explicit Base32File(const char* path, const char* mode);
    Base32File(const char* path, const char* mode, const char* encode_table);
    explicit Base32File(FILE* file);
    
    // деструктор
    virtual ~Base32File();
    
    // переопределенные методы
    virtual size_t write(const void* buf, size_t n_bytes) override;
    virtual size_t read(void* buf, size_t max_bytes) override;
    
    // сброс состояния (важно при seek)
    void reset_state();
    
    // запрещаем копирование (из-за внутреннего состояния)
    Base32File(const Base32File&) = delete;
    Base32File& operator=(const Base32File&) = delete;
};
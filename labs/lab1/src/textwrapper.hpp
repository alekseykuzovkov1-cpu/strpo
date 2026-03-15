#include "mystring.hpp"

class TextWrapper {
private:
    // общие переменные из алгоритма
    MyString text_;          // исходный текст
    int line_width_;         // ширина строки
    int length_;            // длина текста
    int line_len_;          // текущая длина строки
    int word_start_;        // начало текущего слова
    int current_pos_;       // текущая позиция в тексте
    
    // логические условия
    bool is_end_of_word(char ch) const;
    bool is_end_of_text(int pos) const;
    bool word_fits(int word_len) const;
    bool is_word_too_long(int word_len) const;
    
    // принты
    void print_character(char ch);
    void print_spaces(int count);
    void print_word_part(int start, int length);
    void print_full_word(int start, int length);
    
    // управление строками
    void start_new_line();
    void fill_line_to_end();
    void add_space_if_possible();
    
    // обработка разных типов слов
    void process_long_word(int word_len);
    void process_normal_word(int word_len);
    
    // оформление границ
    void print_top_border() const;
    void print_bottom_border() const;
    
public:
    TextWrapper(const MyString& text, int line_width);
    
    // основной метод
    void print_wrapped();
};
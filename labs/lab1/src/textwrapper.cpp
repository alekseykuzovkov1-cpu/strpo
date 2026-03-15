#include "textwrapper.hpp"
#include <iostream>
using namespace std;

// конструктор
TextWrapper::TextWrapper(const MyString& text, int line_width)
    : text_(text)
    , line_width_(line_width)
    , length_(text.length())
    , line_len_(0)
    , word_start_(0)
    , current_pos_(0) {
}

// проверка на конец слова
bool TextWrapper::is_end_of_word(char ch) const {
    return ch == ' ' || ch == '\0';
}

// проверка на конец текста
bool TextWrapper::is_end_of_text(int pos) const {
    return pos >= length_ || text_.get(pos) == '\0';
}

// проверка помещается ли слово в текущую строку
bool TextWrapper::word_fits(int word_len) const {
    return line_len_ + word_len <= line_width_;
}

// проверка на слово длиннее строки
bool TextWrapper::is_word_too_long(int word_len) const {
    return word_len > line_width_;
}

// печать одного символа
void TextWrapper::print_character(char ch) {
    cout << ch;
    line_len_++;
}

// печать нескольких пробелов
void TextWrapper::print_spaces(int count) {
    for (int i = 0; i < count; i++) {
        cout << " ";
        line_len_++;
    }
}

// печать части слова
void TextWrapper::print_word_part(int start, int length) {
    for (int j = 0; j < length; j++) {
        cout << text_.get(start + j);
        line_len_++;
    }
}

// печать целого слова
void TextWrapper::print_full_word(int start, int length) {
    for (int j = start; j < start + length; j++) {
        cout << text_.get(j);
        line_len_++;
    }
}

// начать новую строку
void TextWrapper::start_new_line() {
    // заполняем текущую строку пробелами до конца
    fill_line_to_end();
    cout << " |\n| ";
    line_len_ = 0;
}

// заполнить текущую строку пробелами до конца
void TextWrapper::fill_line_to_end() {
    while (line_len_ < line_width_) {
        cout << " ";
        line_len_++;
    }
}

// добавить пробел после слова, если возможно
void TextWrapper::add_space_if_possible() {
    if (!is_end_of_text(current_pos_) && line_len_ < line_width_) {
        cout << " ";
        line_len_++;
    }
}

// обработка слова, которое длиннее ширины строки
void TextWrapper::process_long_word(int word_len) {
    int chars_remaining = word_len;
    int current_char_pos = word_start_;
    
    while (chars_remaining > 0) {
        int chunk_size = line_width_ - line_len_;
        
        // если текущая строка заполнена
        if (chunk_size == 0) {
            start_new_line();
            chunk_size = line_width_;
        }
        
        // выводим часть слова
        int chars_to_print = (chars_remaining < chunk_size) ? chars_remaining : chunk_size;
        print_word_part(current_char_pos, chars_to_print);
        
        current_char_pos += chars_to_print;
        chars_remaining -= chars_to_print;
        
        // если слово еще не закончилось, переносим на новую строку
        if (chars_remaining > 0 && line_len_ == line_width_) {
            start_new_line();
        }
    }
    
    // добавляем пробел после слова, если не конец текста
    if (!is_end_of_text(current_pos_) && line_len_ < line_width_) {
        print_character(' ');
    }
}

// обработка обычного слова
void TextWrapper::process_normal_word(int word_len) {
    // начинаем новую строку, если слово не влазит
    if (!word_fits(word_len) && line_len_ > 0) {
        start_new_line();
    }
    
    // выводим слово
    if (word_len > 0) {
        print_full_word(word_start_, word_len);
        
        // добавляем пробел после слова, если не конец текста
        if (!is_end_of_text(current_pos_) && line_len_ < line_width_) {
            print_character(' ');
        }
    }
}

// печать верхней границы
void TextWrapper::print_top_border() const {
    cout << ' ';
    for (int i = 0; i < line_width_ + 2; i++) {
        cout << "_";
    }
    cout << endl;
}

// печать нижней границы
void TextWrapper::print_bottom_border() const {
    cout << "|";
    for (int i = 0; i < line_width_ + 2; i++) {
        cout << "_";
    }
    cout << "|" << endl;
}

// основной метод - печать текста с переносом
void TextWrapper::print_wrapped() {

    print_top_border();
    
    // начало первой строки
    cout << "| ";
    line_len_ = 0;
    word_start_ = 0;
    current_pos_ = 0;
    
    // основной цикл обработки текста
    while (current_pos_ <= length_) {
        char current_char = (current_pos_ < length_) ? text_.get(current_pos_) : '\0';
        
        // нашли конец слова
        if (is_end_of_word(current_char)) {
            int word_len = current_pos_ - word_start_;
            
            if (word_len > 0) {
                if (is_word_too_long(word_len)) {
                    process_long_word(word_len);
                } else {
                    process_normal_word(word_len);
                }
            }
            
            word_start_ = current_pos_ + 1;
        }
        
        current_pos_++;
    }
    
    // заполняем последнюю строку пробелами
    fill_line_to_end();
    cout << " |" << endl;
    
    print_bottom_border();
}
#include "barrel.hpp"
#include <stdexcept>
#include <algorithm>
using namespace std;

// пустая бочка
Barrel::Barrel() : volume_(0), alcohol_(0) {}

// бочка заданного объема (пустая)
Barrel::Barrel(double volume) : volume_(volume), alcohol_(0) {
    if (volume < 0) {
        throw invalid_argument("Объем бочки не может быть отрицательным");
    }
}

// бочка с заданным количеством спирта
Barrel::Barrel(double volume, double alcohol) : volume_(volume), alcohol_(alcohol) {
    if (volume < 0) {
        throw invalid_argument("Объем бочки не может быть отрицательным");
    }
    if (alcohol < 0) {
        throw invalid_argument("Количество спирта не может быть отрицательным");
    }
    if (alcohol > volume) {
        throw invalid_argument("Количество спирта не может превышать объем бочки");
    }
}

// получить концентрацию спирта в процентах
double Barrel::get_concentration() const {
    if (volume_ <= 0) return 0.0;
    return (alcohol_ / volume_) * 100.0;
}

// взять определенное количество жидкости из бочки
// возвращает количество взятого спирта
double Barrel::take(double amount) {
    if (amount < 0) {
        throw invalid_argument("Нельзя взять отрицательное количество");
    }
    
    amount = min(amount, volume_);
    double alcohol_taken = (alcohol_ / volume_) * amount;
    
    volume_ -= amount;
    alcohol_ -= alcohol_taken;
    
    return alcohol_taken;
}

// Перелить жидкость из другой бочки в эту
void Barrel::pour_from(Barrel& other, double amount) {
    if (amount < 0) {
        throw invalid_argument("Нельзя перелить отрицательное количество");
    }
    
    double alcohol_taken = other.take(amount);
    
    volume_ += amount;
    alcohol_ += alcohol_taken;
    
}
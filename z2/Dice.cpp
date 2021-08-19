#include "Dice.hpp"

Dice::Dice(std::uniform_int_distribution<int>& distribution, std::mt19937& randomEngine, int value):
    _distribution(distribution),
    _randomEngine(randomEngine),
    _value(testInitValue(value))    
{}

Dice& Dice::operator=(const Dice& dice) {
    _value = dice.value();
    return *this;
}

bool Dice::operator<(const Dice& dice) const {
    return _value < dice.value();
}

int Dice::value() const {
    return _value;
}

void Dice::setValue(int value) {
    _value = testInitValue(value);
}

int Dice::roll() {
    _value = _distribution(_randomEngine);
    return _value;
}

int Dice::testInitValue(const int value) {
    if (value > 6) {
        return 6;
    }
    if (value < 1) {
        return 1;
    }
    return value;
}
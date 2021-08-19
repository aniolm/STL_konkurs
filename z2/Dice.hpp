#pragma once

#include <random>

class Dice {
    std::uniform_int_distribution<int>& _distribution;     
    std::mt19937& _randomEngine;
    int _value;

public:
    Dice(std::uniform_int_distribution<int>& distribution, std::mt19937& randomEngine, int value = -1);

    Dice& operator=(const Dice& dice);

    bool operator<(const Dice& dice) const;
    
	int value() const;

    void setValue(int value);

    int roll();

private:
    int testInitValue(const int value);
};
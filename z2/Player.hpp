#pragma once

#include <array>
#include <string>
#include <random>

#include "Dice.hpp"

class Player {
    std::array<Dice, 5> _dices;

public:
    Player(std::uniform_int_distribution<int>& distribution, std::mt19937& randomEngine);

    std::array<Dice, 5>& dices();

    std::string dicesToString() const;

    void rollAll();
};

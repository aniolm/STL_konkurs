#include <algorithm>

#include "Player.hpp"

Player::Player(std::uniform_int_distribution<int>& distribution, std::mt19937& randomEngine):
    _dices({
        Dice(distribution, randomEngine),
        Dice(distribution, randomEngine),
        Dice(distribution, randomEngine),
        Dice(distribution, randomEngine),
        Dice(distribution, randomEngine)
    })   
{}

std::array<Dice, 5>& Player::dices() {
    return _dices;
}

void Player::rollAll() {
    for (auto& dice : _dices) {
        dice.roll();
    }
    std::sort(_dices.begin(), _dices.end());
}

std::string Player::dicesToString() const {
    std::string result;        
    for (auto& dice : _dices) {
        result += std::to_string(dice.value()) + " "; 
    }
    return result;
}

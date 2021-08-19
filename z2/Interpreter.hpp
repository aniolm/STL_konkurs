#pragma once

#include <array>

#include "Dice.hpp"

enum class Result {
	HigherNumber, 
	OnePair,
	TwoPair, 
	Triplet, 
	Full, 
	Quadruplets, 
	SmallStrit, 
	BigStrit, 
	Poker 
};

Result interpret(const std::array<Dice, 5>& dices);

std::string determineWinner(const Result& playerOne, const Result& playerTwo);

std::string toString(const Result& result);

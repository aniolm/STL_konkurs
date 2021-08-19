#include <algorithm>
#include <map>

#include "Interpreter.hpp"

Result interpret(const std::array<Dice, 5>& dices) {
	std::map<int, int> map;

	for (const auto& dice : dices) {
		++map[dice.value()];
	}
	auto compareQuantity = [](auto& a, auto& b) { return a.second < b.second; };
	const auto& quantity = std::max_element(map.begin(), map.end(), compareQuantity)->second;

	switch (map.size()) {
	case 1:
		return Result::Poker;

	case 2: 
		return (quantity == 4)? Result::Quadruplets : Result::Full;

	case 3: 
		return (quantity == 3)? Result::Triplet : Result::TwoPair;

	case 4:
		return Result::OnePair;

	}
	if (map.find(1) == map.end()) {
		return Result::BigStrit;
	}   
	else if (map.find(6) == map.end()) {
		return Result::SmallStrit;
	}  
	return Result::HigherNumber;
}

std::string determineWinner(const Result& playerOne, const Result& playerTwo) {
	if (playerOne == playerTwo) {
		return "DRAW!!!";
	}
	else if (playerOne > playerTwo) {
		return "PLAYER ONE WINS!!!";
	}
	return "PLAYER TWO WINS!!!";
}

std::string toString(const Result& result) {
	switch (result) {
	case Result::HigherNumber:
		return "HigherNumber";
	
	case Result::OnePair:
		return "OnePair";
	
	case Result::TwoPair:
		return "TwoPair";
	
	case Result::Triplet:
		return "Triplet";
	
	case Result::Full:
		return "Full";
	
	case Result::Quadruplets:
		return "Quadruplets";
	
	case Result::SmallStrit:
		return "SmallStrit";
	
	case Result::BigStrit:
		return "BigStrit";
	
	case Result::Poker:
		return "Poker";

	default:
		return "-1";
	}
}

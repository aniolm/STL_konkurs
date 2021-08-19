#include <algorithm>
#include <array>
#include <random>

#include "catch.hpp"
#include "Player.hpp"

namespace {
	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_int_distribution<int> distribution(1, 6);
}

TEST_CASE("Dice values should be sorted ", "[value(), rollAll()]") {
    WHEN("Dices were rolled multiple times") {
    	Player player(distribution, randomEngine);

		for (size_t i = 0; i < 100; ++i) {
			player.rollAll();
			std::array<int, 5> array;
			for (size_t i = 0; i < 5; ++i) {
				array.at(i) = player.dices().at(i).value();
			}
			std::sort(array.begin(), array.end());

			for (size_t i = 0; i < 5; ++i) {
				const auto diceValue = player.dices().at(i).value();
				THEN("dice value: " + std::to_string(diceValue) + "  required value: " + std::to_string(array.at(i))) {
					REQUIRE(diceValue == array.at(i));
				}
			}
		}
    }
}

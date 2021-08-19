#include <random>

#include "catch.hpp"
#include "Dice.hpp"

namespace {
	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_int_distribution<int> distribution(1, 6);
}

TEST_CASE("Rolled dices should have some value in range", "[value(), roll()]") {
    WHEN("Dice was rolled") {
    	Dice dice(distribution, randomEngine);
		dice.roll();

		THEN("dice value: " + std::to_string(dice.value())) {
			REQUIRE(dice.value() >= 1);
			REQUIRE(dice.value() <= 6);
		}
    }
}

TEST_CASE("Rolled dices shouldn't have the same value triple times in a row", "[value(), roll()]") {
    WHEN("Dice was rolled") {
    	Dice dice(distribution, randomEngine);
		dice.roll();
		auto firstValue = dice.value();

		THEN("dice value: " + std::to_string(dice.value()) + "  first value: " + std::to_string(firstValue)) {
			dice.roll();
			if (dice.value() == firstValue) {
				dice.roll();
			}
			CHECK(dice.value() != firstValue);
		}
    }
}

TEST_CASE("Dices value can be set", "[value(), setValue()]") {
	Dice dice(distribution, randomEngine);

    WHEN("Dice value was set inbound") {
		for (int i = 1; i <= 6; ++i) {
			dice.setValue(i);
			THEN("dice value: " + std::to_string(dice.value()) + "  wanted value: " + std::to_string(i)) {
				REQUIRE(dice.value() == i);
			}
		}
    }
	WHEN("Dice value was to low") {
		for (int i = -3; i <= 0; ++i) {
			dice.setValue(i);
			THEN("dice value: " + std::to_string(dice.value()) + "  wanted value: " + std::to_string(1)) {
				REQUIRE(dice.value() == 1);
			}
		}
    }
	WHEN("Dice value was to low") {
		for (int i = 9; i <= 7; --i) {
			dice.setValue(i);
			THEN("dice value: " + std::to_string(dice.value()) + "  wanted value: " + std::to_string(6)) {
				REQUIRE(dice.value() == 6);
			}
		}
    }
}

TEST_CASE("Dices value can be set by constructor", "[value(), setValue()]") {
    WHEN("Dice value was set inbound") {
		for (int i = 1; i <= 6; ++i) {
			Dice dice(distribution, randomEngine, i);
			THEN("dice value: " + std::to_string(dice.value()) + "  wanted value: " + std::to_string(i)) {
				REQUIRE(dice.value() == i);
			}
		}
    }
	WHEN("Dice value was to low") {
		for (int i = -3; i <= 0; ++i) {
			Dice dice(distribution, randomEngine, i);
			THEN("dice value: " + std::to_string(dice.value()) + "  wanted value: " + std::to_string(1)) {
				REQUIRE(dice.value() == 1);
			}
		}
    }
	WHEN("Dice value was to low") {
		for (int i = 9; i <= 7; --i) {
			Dice dice(distribution, randomEngine, i);
			THEN("dice value: " + std::to_string(dice.value()) + "  wanted value: " + std::to_string(6)) {
				REQUIRE(dice.value() == 6);
			}
		}
    }
}

#include <random>

#include "catch.hpp"
#include "Interpreter.hpp"

namespace {
	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_int_distribution<int> distribution(1, 6);
}

TEST_CASE("Result values indicates their priorities", "[Result::]") {
	WHEN("In default state") {
		THEN("Poker is better then BigStrit") {
			REQUIRE(Result::Poker > Result::BigStrit);
		}
		THEN("BigStrit is better then SmallStrit") {
			REQUIRE(Result::BigStrit > Result::SmallStrit);
		}
		THEN("SmallStrit is better then Quadruplets") {
			REQUIRE(Result::SmallStrit > Result::Quadruplets);
		}
		THEN("Quadruplets is better then Full") {
			REQUIRE(Result::Quadruplets > Result::Full);
		}
		THEN("Full is better then Triplet") {
			REQUIRE(Result::Full > Result::Triplet);
		}
		THEN("Triplet is better then TwoPair") {
			REQUIRE(Result::Triplet > Result::TwoPair);
		}
		THEN("TwoPair is better then OnePair") {
			REQUIRE(Result::TwoPair > Result::OnePair);
		}
		THEN("OnePair is better then HigherNumber") {
			REQUIRE(Result::OnePair > Result::HigherNumber);
		}
	}
}

TEST_CASE("Interpreter main operation", "[interpet()]") {
    struct Test {
		const std::array<const int, 5> initValues;
		const Result expectedResult;

		const std::array<Dice, 5> createDices() const {
			return {
				Dice(distribution, randomEngine, initValues.at(0)),
				Dice(distribution, randomEngine, initValues.at(1)),
				Dice(distribution, randomEngine, initValues.at(2)),
				Dice(distribution, randomEngine, initValues.at(3)),
				Dice(distribution, randomEngine, initValues.at(4))
			};
		}

        std::string log() const {
			std::string result = "{ ";     
			auto dices = createDices();

			for (const auto& dice : dices) {
				result += std::to_string(dice.value()) + " "; 
			}
			result += "}, Expected Result: " + toString(expectedResult);
			return result;
        }
    };

	auto runTests = [](const std::initializer_list<Test>& tests) {
        for (const auto& test : tests) {			
			auto dices = test.createDices();
			for (size_t i = 0; i < 5; ++i) {
				REQUIRE(test.initValues.at(i) == dices.at(i).value());
			}
            THEN(test.log()) {
				REQUIRE(interpret(dices) == test.expectedResult);
            }
        }
	};

	WHEN("Testing the Poker figure") {
        std::initializer_list<Test> tests = {
			{{1,1,1,1,1}, Result::Poker},
			{{2,2,2,2,2}, Result::Poker},
			{{3,3,3,3,3}, Result::Poker},
			{{4,4,4,4,4}, Result::Poker},
			{{5,5,5,5,5}, Result::Poker},
			{{6,6,6,6,6}, Result::Poker},
		};
		runTests(tests);
	}
	WHEN("Testing the BigStrit figure") {
        std::initializer_list<Test> tests = {
			{{2,3,4,5,6}, Result::BigStrit},
			{{6,2,3,4,5}, Result::BigStrit},
			{{3,5,2,4,6}, Result::BigStrit}
		};
		runTests(tests);
	}
	WHEN("Testing the SmallStrit figure") {
        std::initializer_list<Test> tests = {
			{{1,2,3,4,5}, Result::SmallStrit},
			{{5,1,2,3,4}, Result::SmallStrit},
			{{3,5,2,4,1}, Result::SmallStrit}
		};
		runTests(tests);
	}
	WHEN("Testing the Quadruplets figure") {
        std::initializer_list<Test> tests = {
			{{1,1,1,1,2}, Result::Quadruplets},
			{{2,1,2,2,2}, Result::Quadruplets},
			{{6,5,5,5,5}, Result::Quadruplets},
			{{2,2,2,6,2}, Result::Quadruplets}
		};
		runTests(tests);
	}
	WHEN("Testing the Full figure") {
        std::initializer_list<Test> tests = {
			{{1,1,1,2,2}, Result::Full},
			{{2,1,2,1,2}, Result::Full},
			{{6,6,5,5,5}, Result::Full},
			{{4,2,2,4,2}, Result::Full}
		};
		runTests(tests);
	}
	WHEN("Testing the Triplet figure") {
        std::initializer_list<Test> tests = {
			{{1,1,1,2,4}, Result::Triplet},
			{{2,1,2,3,2}, Result::Triplet},
			{{6,1,5,5,5}, Result::Triplet},
			{{3,2,2,4,2}, Result::Triplet}
		};
		runTests(tests);
	}
	WHEN("Testing the TwoPair figure") {
        std::initializer_list<Test> tests = {
			{{1,1,2,2,4}, Result::TwoPair},
			{{3,1,2,3,2}, Result::TwoPair},
			{{6,6,3,5,5}, Result::TwoPair},
			{{3,2,2,4,4}, Result::TwoPair}
		};
		runTests(tests);
	}
	WHEN("Testing the OnePair figure") {
        std::initializer_list<Test> tests = {
			{{1,1,6,2,4}, Result::OnePair},
			{{3,1,2,5,2}, Result::OnePair},
			{{6,4,3,5,5}, Result::OnePair},
			{{3,2,2,6,4}, Result::OnePair}
		};
		runTests(tests);
	}
	WHEN("Testing the HigherNumber figure") {
        std::initializer_list<Test> tests = {
			{{1,3,4,5,6}, Result::HigherNumber},
			{{2,1,4,5,6}, Result::HigherNumber},
			{{2,3,1,5,6}, Result::HigherNumber},
			{{2,3,4,1,6}, Result::HigherNumber},
			{{1,6,3,4,5}, Result::HigherNumber},
			{{1,2,6,4,5}, Result::HigherNumber},
			{{1,2,3,6,5}, Result::HigherNumber},
			{{1,2,3,4,6}, Result::HigherNumber}
		};
		runTests(tests);
	}
}

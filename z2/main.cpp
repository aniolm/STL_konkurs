#include <iostream>
#include <random>

#include "Interpreter.hpp"
#include "Player.hpp"

int main() {
    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());
    std::uniform_int_distribution<int> distribution(1, 6);

    Player playerOne(distribution, randomEngine);
    Player playerTwo(distribution, randomEngine);

    playerOne.rollAll();
    playerTwo.rollAll();

    auto playerOneResult = interpret(playerOne.dices());
    auto playerTwoResult = interpret(playerTwo.dices());
    
    std::cout << "\n player one: " << playerOne.dicesToString() << "-> [" << toString(playerOneResult) << "]"
        << "\n player two: " << playerTwo.dicesToString() << "-> [" << toString(playerTwoResult) << "]"
        << "\n\n " << determineWinner(playerOneResult, playerTwoResult)
        << "\n\n";    

    return 0;
}  

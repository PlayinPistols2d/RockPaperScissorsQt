#include "computerai.h"
#include <cstdlib>
#include <ctime>

ComputerAi::ComputerAi()
{
    std::srand(std::time(0));
}

gameOptions ComputerAi::makeDescision()
{
    int randomChoice = std::rand() % 3;
    switch(randomChoice) {
    case rock : return rock; break;
    case paper : return paper; break;
    case scissors : return scissors; break;
    //default should never be reached
    };
}

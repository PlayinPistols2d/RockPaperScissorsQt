#ifndef COMPUTERAI_H
#define COMPUTERAI_H

enum gameOptions {
    rock,
    paper,
    scissors
};

class ComputerAi
{
public:
    ComputerAi();
    gameOptions makeDescision();
};

#endif // COMPUTERAI_H

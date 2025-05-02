#ifndef MISTAKE_H
#define MISTAKE_H

#include "bracket.h"


class mistake
{
public:
    mistake();
    enum MistakeWithBracketsType{
        UnclosedBracket,
        ExcessiveClosingBracket,
        IncorrectOrderOfBrackets
    };

    mistake (bracket foundBracket, MistakeWithBracketsType type);

    MistakeWithBracketsType type;
    bracket bracketWithMistake;
};

#endif // MISTAKE_H

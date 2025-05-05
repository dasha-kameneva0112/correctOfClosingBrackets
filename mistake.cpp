#include "mistake.h"

mistake::mistake() {}


mistake::mistake (bracket foundBracket, MistakeWithBracketsType currentType)
{
    type = currentType;
    bracketWithMistake = foundBracket;
}

MistakeWithBracketsType mistake::getType() const
{    return this->type;  }

bracket mistake::getBracket() const
{    return this->bracketWithMistake;    }

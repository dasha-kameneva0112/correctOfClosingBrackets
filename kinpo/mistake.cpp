#include "mistake.h"

mistake::mistake() {}


mistake::mistake (bracket foundBracket, MistakeWithBracketsType currentType)
{
    type = currentType;
    bracketWithMistake = foundBracket;
}

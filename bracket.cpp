#include "bracket.h"

bracket::bracket() {}

bracket::bracket(BracketType currentType, BracketSide currentSide)
{
    type=currentType;
    side=currentSide;
    numberOfLine = 0;
    positionOfBraket = 0;
    correctOfOrder = true;
}

bracket::bracket (const QStringList& code, int indexOfLineWithBracket, int position)
{
    // Получаем строку и символ скобки
    const QString line = code[indexOfLineWithBracket];
    QChar currentBracket = line[position];

    // тип скобки
    switch (currentBracket.toLatin1())
    {
    case ('('):
    case (')'):
        type = Round;
        break;
    case ('['):
    case (']'):
        type = Square;
        break;
    case ('{'):
    case ('}'):
        type = Curly;
        break;
    }

    // сторона скобки
    switch (currentBracket.toLatin1())
    {
    case ('('):
    case ('['):
    case ('{'):
        side = Opening;
        break;
    case (')'):
    case (']'):
    case ('}'):
        side = Closing;
        break;
    }

    numberOfLine = indexOfLineWithBracket;
    positionOfBraket = position;
    correctOfOrder = true;  // По умолчанию считаем порядок правильным

}

BracketType bracket::getType() const
{    return this->type; }

BracketSide bracket::getSide() const
{    return this->side; }

int bracket::getPosition() const
{    return this->positionOfBraket; }

int bracket::getLine() const
{    return this->numberOfLine; }

bool bracket::getOrder() const
{    return this->correctOfOrder; }


void bracket::setOrder(bool order)
{ this->correctOfOrder = order; }
/*hgbhhh*/

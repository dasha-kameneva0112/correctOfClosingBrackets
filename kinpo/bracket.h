#ifndef BRACKET_H
#define BRACKET_H
#include <QStringList>


class bracket
{
public:
    bracket();
    bracket (const QStringList& code, int indexOfLineWithBracket, int position);

    enum BracketType{
        Round,
        Square,
        Curly
    };
    enum BracketSide{
        Opening,
        Closing
    };

    BracketType type;
    BracketSide side;
    int numberOfLine; //номер строки кода с данной скобкой
    int positionOfBraket; //позиция скобки в строке
    bool correctOfOrder; //правильность порядка скобки
};

#endif // BRACKET_H

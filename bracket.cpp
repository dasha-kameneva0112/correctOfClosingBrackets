#include "bracket.h"

bracket::bracket() {}


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

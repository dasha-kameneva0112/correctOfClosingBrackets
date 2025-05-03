#ifndef MISTAKE_H
#define MISTAKE_H

#include <QHash>
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

    mistake (bracket foundBracket, MistakeWithBracketsType currentType);

    MistakeWithBracketsType type;
    bracket bracketWithMistake;

    bool operator==(const mistake& other) const
    {
        return (type == other.type && bracketWithMistake == other.bracketWithMistake);
    }
};

inline size_t qHash(const mistake& key, size_t seed = 0) noexcept
{
    // Комбинируем хэши всех полей, которые участвуют в operator==
    QtPrivate::QHashCombine hash;
    seed = hash(seed, static_cast<int>(key.type)); // для enum
    seed = hash(seed, qHash(key.bracketWithMistake)); // для bracket (без seed, иначе хеш будет зависеть от seed)
    return seed;
}

#endif // MISTAKE_H

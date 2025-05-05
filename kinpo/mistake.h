#ifndef MISTAKE_H
#define MISTAKE_H

#include <QHash>
#include "bracket.h"

enum MistakeWithBracketsType{
    UnclosedBracket,
    ExcessiveClosingBracket,
    IncorrectOrderOfBrackets
};

class mistake
{
public:
    mistake();
    mistake (bracket foundBracket, MistakeWithBracketsType currentType);
    MistakeWithBracketsType getType() const;
    bracket getBracket() const;

    bool operator==(const mistake& other) const
    {
        return (type == other.type && bracketWithMistake == other.bracketWithMistake);
    }

private:
    MistakeWithBracketsType type;
    bracket bracketWithMistake;
};

inline size_t qHash(const mistake& key, size_t seed = 0) noexcept
{
    // Комбинируем хэши всех полей, которые участвуют в operator==
    QtPrivate::QHashCombine hash;
    seed = hash(seed, static_cast<int>(key.getType())); // для enum
    seed = hash(seed, qHash(key.getBracket())); // для bracket (без seed, иначе хеш будет зависеть от seed)
    return seed;
}

#endif // MISTAKE_H

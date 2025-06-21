#ifndef MISTAKE_H
#define MISTAKE_H

#include <QHash>
#include "bracket.h"

/*!
 * \enum MistakeWithBracketsType
 * \brief Типы ошибок, связанных со скобками
 */
enum MistakeWithBracketsType{
    UnclosedBracket, ///< Незакрытая скобка
    ExcessiveClosingBracket, ///< Избыточная закрывающая скобка
    IncorrectOrderOfBrackets ///< Неправильный порядок скобок
};


/*!
 * \class mistake
 * \brief Класс для хранения информации об ошибках в использовании скобок
 * Содержит тип ошибки и связанную с ней скобку.
 */
class mistake
{
public:
    /*!
     * \brief mistake - конструктор по умолчанию
     */
    mistake();

    /*!
     * \brief mistake - конструктор с параметрами (тип ошибки и скобка)
     * \param foundBracket - найденная скобка с ошибкой
     * \param currentType - тип ошибки
     */
    mistake (bracket foundBracket, MistakeWithBracketsType currentType);

    /*!
     * \brief getType - метод, который возвращает тип ошибки
     * \return type - тип ошибки
     */
    MistakeWithBracketsType getType() const;

    /*!
     * \brief getBracket - метод, который возвращает скобку с ошибкой
     * \return bracketWithMistake - скобка с ошибкой
     */
    bracket getBracket() const;

    /*!
     * \brief operator == - оператор сравнения ошибок со скобками
     * \param other - сравниваемый объект mistake
     * \return true, если ошибки идентичны, false - если нет
     */
    bool operator==(const mistake& other) const
    {
        return (type == other.type && bracketWithMistake == other.bracketWithMistake);
    }

private:
    MistakeWithBracketsType type; ///< Тип ошибки
    bracket bracketWithMistake; ///< Скобка с ошибкой
};


/*!
 * \brief qHash - хеш-функция для класса mistake, необходимая для использования mistake в QSet
 * \param key - объект ошибки
 * \param seed - начальное значение хеша
 * \return seed - хеш-значение
 */
inline size_t qHash(const mistake& key, size_t seed = 0) noexcept
{
    // Комбинируем хэши всех полей, которые участвуют в operator==
    QtPrivate::QHashCombine hash;
    seed = hash(seed, static_cast<int>(key.getType())); // для enum
    seed = hash(seed, qHash(key.getBracket())); // для bracket (без seed, иначе хеш будет зависеть от seed)
    return seed;
}

#endif // MISTAKE_H

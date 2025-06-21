#ifndef BRACKET_H
#define BRACKET_H
#include <QStringList>
#include <functional>

/*!
 * \enum BracketType
 * \brief Типы скобок для проверки
 */
enum BracketType{
    Round, ///< Круглые скобки `()`
    Square, ///< Квадратные скобки `[]`
    Curly ///< Фигурные скобки `{}`
};

/*!
 * \enum BracketSide
 * \brief Направление скобки
 */
enum BracketSide{
    Opening, ///< Открывающая скобка
    Closing ///< Закрывающая скобка
};

/*!
 * \class bracket
 * \brief Хранит информацию о скобке в коде
 * Класс отслеживает тип, направление, положение в коде и корректность скобки с соседней
 */
class bracket
{
public:
    /*!
     * \brief bracket - конструктор по умолчанию
     */
    bracket();

    /*!
     * \brief bracket - конструктор с параметрами (позиция в коде)
     * \param code - исходный код
     * \param indexOfLineWithBracket - номер строки
     * \param position - позиция в строке
     * \param order - флаг корректности порядка с соседней скобкой
     */
    bracket (const QStringList& code, int indexOfLineWithBracket, int position, bool order=true);

    /*!
     * \brief bracket - конструктор с параметрами (тип и направление)
     * \param currentType - тип скобки
     * \param currentSide - направление скобки
     */
    bracket(BracketType currentType, BracketSide currentSide);

    /*!
     * \brief getType - метод, который возвращает тип скобки
     * \return type - тип данной скобки
     */
    BracketType getType() const;

    /*!
     * \brief getSide - метод, который возвращает направление скобки
     * \return side - направление данной скобки
     */
    BracketSide getSide() const;

    /*!
     * \brief getPosition - метод, который возвращает позицию скобки в строке
     * \return positionOfBraket - позиция в строке данной скобки
     */
    int getPosition() const;

    /*!
     * \brief getLine - метод, который возвращает номер строки в коде со скобкой
     * \return numberOfLine - номер строки в коде с данной скобкой
     */
    int getLine() const;

    /*!
     * \brief getOrder - метод, который возвращает корректность порядка скобки с соседней
     * \return correctOfOrder - флаг корректности порядка данной скобки с предыдущей соседней
     */
    bool getOrder() const;

    /*!
     * \brief setOrder - метод, который устанавливает для скобки данный порядок с соседней
     * \param order - указанный флаг корректности порядка
     */
    void setOrder(bool order);

    /*!
     * \brief operator == - оператор сравнения скобок
     * \param other - сравниваемая скобка bracket
     * \return true - если все поля совпадают, иначе - false
     */
    bool operator==(const bracket& other) const
    {
        return (type == other.type && side == other.side &&
                numberOfLine == other.numberOfLine &&
                positionOfBraket == other.positionOfBraket && correctOfOrder == other.correctOfOrder);
    }

private:
    BracketType type; ///< Тип скобки
    BracketSide side; ///< Направление скобки
    int numberOfLine; ///< Номер строки в коде со скобкой
    int positionOfBraket; ///< Позиция скобки в строке
    bool correctOfOrder; ///< Флаг корректности порядка скобки с предыдущей соседней
};

/*!
 * \brief qHash - хеш-функция для класса bracket, необходимая для использования bracket в QSet
 * \param key - объект скобки
 * \param seed - начальное значение хеша
 * \return уникальный хеш-код
 */
inline size_t qHash(const bracket& key, size_t seed = 0) noexcept
{
    // Комбинируем хеши всех полей, которые участвуют в operator==
    return qHashMulti(seed,
                      static_cast<int>(key.getType()),
                      static_cast<int>(key.getSide()),
                      key.getLine(),
                      key.getPosition(),
                      key.getOrder());
}

#endif // BRACKET_H

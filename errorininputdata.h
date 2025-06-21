#ifndef ERRORININPUTDATA_H
#define ERRORININPUTDATA_H


/*!
 * \enum ErrorsInInputDataType
 * \brief Типы ошибок входных данных
 * Перечисление содержит все возможные ошибки, связанные с обработкой входных данных программы.
 */
enum ErrorsInInputDataType {
    NoError,  ///< Нет ошибки
    NoAccessToInputFile, ///< Нет доступа к входному файлу
    NoAccessToOutputFile, ///< Нет доступа к выходному файлу
    EmptyInputFile, ///< Входной файл пуст
    UnclosedMultilineComment, ///< Незакрытый многострочный комментарий
    UnclosedStringConst, ///< Незакрытая строковая константа
    UnclosedCharConst, ///< Незакрытая символьная константа
    IncorrectFileExtension, ///< Некорректное расширение файла
    ExceedingMaxLengthInputFile ///< Превышена максимальная длина входного файла
};


/*!
 * class errorininputdata
 * \brief Класс для хранения информации об ошибке входных данных
 * Содержит тип ошибки, номер строки и позицию в строке, где была обнаружена ошибка.
 */
class errorininputdata
{
public:
    /*!
     * \brief errorininputdata - конструктор по умолчанию
     */
    errorininputdata();

    /*!
     * \brief errorininputdata - конструктор с 1 параметром (тип ошибки)
     * \param currentType - тип ошибки
     */
    errorininputdata(ErrorsInInputDataType currentType);

    /*!
     * \brief errorininputdata - конструктор с параметрами (тип ошибки, номер строки и позиция в строке)
     * \param currentType - тип ошибки
     * \param indexOfLineWithError - номер строки кода с ошибкой
     * \param position - позиция ошибки в строке
     */
    errorininputdata(ErrorsInInputDataType currentType, int indexOfLineWithError, int position);

    /*!
     * \brief updateError - метод, который обновляет информацию об ошибке
     * \param currentType - новый тип ошибки
     * \param indexOfLineWithError - новый номер строки кода с ошибкой
     * \param position - новая позиция ошибки в строке
     */
    void updateError(ErrorsInInputDataType currentType, int indexOfLineWithError, int position);

    /*!
     * \brief getType - метод, который возвращает тип ошибки
     * \return type - тип данной ошибки
     */
    ErrorsInInputDataType getType() const;

    /*!
     * \brief getLine - метод, который возвращает номер строки кода с ошибкой
     * \return numberOfLine - номер строки в коде с данной ошибкой
     */
    int getLine() const;

    /*!
     * \brief getPosition - метод, который возвращает позицию ошибки в строке
     * \return positionOfError - позиция данной ошибки в строке
     */
    int getPosition() const;

    /*!
     * \brief setType - метод, который устанавливает новый тип у ошибки
     * \param new_type - новый тип ошибки
     */
    void setType(ErrorsInInputDataType new_type);

    /*!
     * \brief setLine - метод, который устанавливает новый номер строки в коде с ошибкой
     * \param line - новый номер строки в коде с ошибкой
     */
    void setLine(int line);

    /*!
     * \brief setPos - метод, который устанавливает новую позицию ошибки в строке
     * \param pos - новая позиция ошибки в строке
     */
    void setPos(int pos);

    /*!
     * \brief operator == - оператор сравнения ошибок входных данных
     * \param other - сравниваемый объект errorininputdata
     * \return true, если ошибки идентичны, иначе - false
     */
    bool operator==(const errorininputdata& other) const
    {
        return (type == other.type && numberOfLine == other.numberOfLine &&
                positionOfError == other.positionOfError);
    }

private:
    ErrorsInInputDataType type=NoError; ///< Тип ошибки
    int numberOfLine=-1; ///< Номер строки кода с ошибкой
    int positionOfError=-1; ///< Позиция ошибки в строке
};

#endif // ERRORININPUTDATA_H

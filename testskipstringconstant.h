/*!
 *\file testskipstringconstant.h
 *\brief  Заголовочный файл для класса testskipstringconstant
 *\file testskipstringconstant.cpp
 *\brief Реализация тестов для функции skipStringConstant
*/

#ifndef TESTSKIPSTRINGCONSTANT_H
#define TESTSKIPSTRINGCONSTANT_H
#include <QObject>
#include "main.h"

class testskipstringconstant : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testskipstringconstant(QObject *parent = nullptr);

private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Проверяет корректность обработки строковых констант:
     * - Пропуск стандартных строк в двойных кавычках
     * - Обработку экранированных символов
     * - Выявление незакрытых строк
     * - Обработку многострочных строковых констант
     */
    void add_data();

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции пропуска строковых констант в коде skipStringConstant
     */
    void add();
};



#endif // TESTSKIPSTRINGCONSTANT_H

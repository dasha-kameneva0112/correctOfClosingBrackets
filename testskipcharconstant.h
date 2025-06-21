/*!
 *\file testskipcharconstant.h
 *\brief  Заголовочный файл для класса testskipcharconstant
 *\file testskipcharconstant.cpp
 *\brief Реализация тестов для функции skipCharConstant
*/

#ifndef TESTSKIPCHARCONSTANT_H
#define TESTSKIPCHARCONSTANT_H
#include <QObject>
#include "main.h"

class testskipcharconstant : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testskipcharconstant(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Проверяет корректность обработки символьных констант:
     * - Пропуск корректных констант
     * - Обработку экранированных символов
     * - Выявление ошибок в константах
     */
    void add_data();

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции пропуска символьных констант в коде skipCharConstant
     */
    void add();
};

#endif // TESTSKIPCHARCONSTANT_H

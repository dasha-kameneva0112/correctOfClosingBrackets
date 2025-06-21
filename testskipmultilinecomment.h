/*!
 *\file testskipmultilinecomment.h
 *\brief  Заголовочный файл для класса testskipmultilinecomment
 *\file testskipmultilinecomment.cpp
 *\brief Реализация тестов для функции skipMultilineComment
*/

#ifndef TESTSKIPMULTILINECOMMENT_H
#define TESTSKIPMULTILINECOMMENT_H
#include <QObject>
#include "main.h"

class testskipmultilinecomment : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    testskipmultilinecomment(QObject *parent = nullptr);

private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Проверяет корректность обработки многострочных комментариев:
     * - Пропуск корректных комментариев (разных форматов)
     * - Обработку экранированных символов внутри комментариев
     * - Выявление незакрытых комментариев
     */
    void add_data(); //В этом слоте создается таблица данных

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции пропуска многострочных комментариев в коде skipMultilineComment
     */
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTSKIPMULTILINECOMMENT_H


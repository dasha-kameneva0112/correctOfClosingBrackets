/*!
 *\file testfindnextbracket.h
 *\brief  Заголовочный файл для класса testfindnextbracket
 *\file testfindnextbracket.cpp
 *\brief Реализация тестов для функции findNextBracket
*/

#ifndef TESTFINDNEXTBRACKET_H
#define TESTFINDNEXTBRACKET_H
#include <QObject>
#include "main.h"


class testfindnextbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindnextbracket(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Проверяет корректность поиска следующей скобки в коде с учетом:
     * - Пропуска комментариев (однострочных и многострочных)
     * - Пропуска строковых и символьных констант
     * - Обработки ошибок в константах и комментариях
     */
    void add_data();

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции поиска следующей скобки findNextBracket
     */
    void add();
};

#endif // TESTFINDNEXTBRACKET_H

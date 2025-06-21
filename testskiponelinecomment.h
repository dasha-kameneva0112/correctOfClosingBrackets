/*!
 *\file testskiponelinecomment.h
 *\brief  Заголовочный файл для класса testskiponelinecomment
 *\file testskiponelinecomment.cpp
 *\brief Реализация тестов для функции skipOneLineComment
*/

#ifndef TESTSKIPONELINECOMMENT_H
#define TESTSKIPONELINECOMMENT_H
#include <QObject>
#include "main.h"

class testskiponelinecomment : public QObject //Наследование от QObject
{
    Q_OBJECT //Обязательный макрос
public:
    testskiponelinecomment(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Проверяет корректность обработки однострочных комментариев:
     * - Пропуск стандартных комментариев
     * - Обработку комментариев с экранированными символами
     * - Пропуск пустых комментариев
     * - Обработку комментариев в конце кода
     */
    void add_data(); //В этом слоте создается таблица данных

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции пропуска однострочных комментариев skipOneLineComment
     */
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTSKIPONELINECOMMENT_H

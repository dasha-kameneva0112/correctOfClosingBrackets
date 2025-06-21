/*!
 *\file testfindcoupleforbracket.h
 *\brief  Заголовочный файл для класса testfindcoupleforbracket
 *\file testfindcoupleforbracket.cpp
 *\brief Реализация тестов для функции findCoupleForBracket
*/

#ifndef TESTFINDCOUPLEFORBRACKET_H
#define TESTFINDCOUPLEFORBRACKET_H
#include <QObject>
#include "main.h"

class testfindcoupleforbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindcoupleforbracket(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций для проверки поиска парных скобок
     * Создает тестовые случаи, включая:
     * - Разные типы скобок (круглые, квадратные, фигурные)
     * - Случай с несколькими скобками одного типа в стеке
     * - Случай когда пара не найдена
     * - Случай с пустым стеком
     */
    void add_data(); //В этом слоте создается таблица данных

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции поиска парной скобки findCoupleForBracket
     */
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTFINDCOUPLEFORBRACKET_H

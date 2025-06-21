/*!
 *\file testconstructorbracket.h
 *\brief  Заголовочный файл для класса testconstructorbracket
 *\file testconstructorbracket.cpp
 *\brief Реализация тестов для конструктора bracket
*/

#ifndef TESTCONSTRUCTORBRACKET_H
#define TESTCONSTRUCTORBRACKET_H
#include <QObject>
#include "main.h"

/*!
 * \class testconstructorbracket
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки конструктора класса bracket
 *
 * Этот класс предоставляет набор тестов для проверки корректности создания объектов скобок различных типов.
 */
class testconstructorbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testconstructorbracket(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Создает таблицу тестовых данных с различными вариантами скобок:
     * - Открывающие/закрывающие
     * - Разные типы (круглые, квадратные, фигурные)
     * - Разные позиции в коде
     * - Проверка правильности порядка
     */
    void add_data();

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование конструктора bracket.
     */
    void add();
};

#endif // TESTCONSTRUCTORBRACKET_H

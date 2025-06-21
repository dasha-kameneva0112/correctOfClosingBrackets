/*!
 *\file testfindallincorrectusesofbrackets.h
 *\brief  Заголовочный файл для класса testfindallincorrectusesofbrackets
 *\file testfindallincorrectusesofbrackets.cpp
 *\brief Реализация тестов для функции findAllIncorrectUsesOfBrackets
*/

#ifndef TESTFINDALLINCORRECTUSESOFBRACKETS_H
#define TESTFINDALLINCORRECTUSESOFBRACKETS_H
#include <QObject>
#include "main.h"

class testfindallincorrectusesofbrackets : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindallincorrectusesofbrackets(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Метод создает тестовые случаи, включая:
     *  - Корректный код со скобками
     *  - Код с комментариями и константами
     *  - Различные типы ошибок (лишние, незакрытые, неправильный порядок скобок)
     *  - Ошибки в строковых и символьных константах
     *  - Незакрытые многострочные комментарии
     */
    void add_data();

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции поиска использования некорректных скобок findAllIncorrectUsesOfBrackets
     */
    void add();
};

#endif // TESTFINDALLINCORRECTUSESOFBRACKETS_H

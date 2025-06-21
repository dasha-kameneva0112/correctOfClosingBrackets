/*!
 *\file testupdateconteinerofbrackets.h
 *\brief  Заголовочный файл для класса testupdateconteinerofbrackets
 *\file testupdateconteinerofbrackets.cpp
 *\brief Реализация тестов для функции updateContainerOfBrackets
*/

#ifndef TESTUPDATECONTEINEROFBRACKETS_H
#define TESTUPDATECONTEINEROFBRACKETS_H
#include <QObject>
#include "main.h"

class testupdateconteinerofbrackets : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testupdateconteinerofbrackets(QObject *parent = nullptr);
private slots:
    /*!
     * \brief add_data - заполнение данными тестовых ситуаций
     * Проверяет корректность обновления стека скобок и обнаружения ошибок:
     * - Добавление открывающих и закрывающих скобок
     * - Обнаружение лишних закрывающих скобок
     * - Проверка правильности порядка скобок
     * - Обработка комплексных случаев вложенности
     */
    void add_data();

    /*!
     * \brief add - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции обновления контейнера скобок и обнаружения ошибок updateContainerOfBrackets
     */
    void add();
};

#endif // TESTUPDATECONTEINEROFBRACKETS_H




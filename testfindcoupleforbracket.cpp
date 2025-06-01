#include "testfindcoupleforbracket.h"
#include <QStack>

testfindcoupleforbracket::testfindcoupleforbracket(QObject *parent) : QObject(parent) {}

void testfindcoupleforbracket::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<bracket>("newBracket");
    QTest::addColumn<QStack<bracket>>("brackets");
    QTest::addColumn<int>("indexofbracket");

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1.1. Круглая скобка
    QStringList code_1 = {")"};
    bracket newBracket1(code_1, 0, 0);

    QStringList code1 = {"( { ["};
    QStack<bracket> brackets1;
    brackets1.push(bracket(code1, 0, 0));
    brackets1.push(bracket(code1, 0, 2));
    brackets1.push(bracket(code1, 0, 4));
    QTest::newRow("roundBracket") << newBracket1 << brackets1 << 0;

    // №1.2. Квадратная скобка
    QStringList code_2 = {"]"};
    bracket newBracket2(code_2, 0, 0);

    QStringList code2 = {"( { ["};
    QStack<bracket> brackets2;
    brackets2.push(bracket(code2, 0, 0));
    brackets2.push(bracket(code2, 0, 2));
    brackets2.push(bracket(code2, 0, 4));
    QTest::newRow("squareBracket") << newBracket2 << brackets2 << 2;

    // №1.3. Фигурная скобка
    QStringList code_3 = {"}"};
    bracket newBracket3(code_3, 0, 0);

    QStringList code3 = {"( { ["};
    QStack<bracket> brackets3;
    brackets3.push(bracket(code3, 0, 0));
    brackets3.push(bracket(code3, 0, 2));
    brackets3.push(bracket(code3, 0, 4));
    QTest::newRow("curlyBracket") << newBracket3 << brackets3 << 1;

    // №2. В стеке есть несколько (3-4) скобок того же типа
    QStringList code_4 = {")"};
    bracket newBracket4(code_4, 0, 0);

    QStringList code4 = {"( { ( [ ("};
    QStack<bracket> brackets4;
    brackets4.push(bracket(code4, 0, 0));
    brackets4.push(bracket(code4, 0, 2));
    brackets4.push(bracket(code4, 0, 4));
    brackets4.push(bracket(code4, 0, 6));
    brackets4.push(bracket(code4, 0, 8));
    QTest::newRow("multipleBracketsOfTheSameType") << newBracket4 << brackets4 << 4;

    // №3. В стеке нет пары
    QStringList code_5 = {"}"};
    bracket newBracket5(code_5, 0, 0);

    QStringList code5 = {"( [ ( [ ("};
    QStack<bracket> brackets5;
    brackets5.push(bracket(code5, 0, 0));
    brackets5.push(bracket(code5, 0, 2));
    brackets5.push(bracket(code5, 0, 4));
    brackets5.push(bracket(code5, 0, 6));
    brackets5.push(bracket(code5, 0, 8));
    QTest::newRow("thereIsNoCouple") << newBracket5 << brackets5 << -1;

    //№4. Стек пустой
    QStringList code6 = {")"};
    bracket newBracket6(code6, 0, 0);
    QStack<bracket> brackets6;
    QTest::newRow("theStackIsEmpty") << newBracket6 << brackets6 << -1;
}

void testfindcoupleforbracket::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные
    QFETCH(bracket, newBracket);
    QFETCH(QStack<bracket>, brackets);
    QFETCH(int, indexofbracket);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    int result = findCoupleForBracket(newBracket, brackets);
    QCOMPARE(result, indexofbracket);
}


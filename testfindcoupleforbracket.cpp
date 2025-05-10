#include "testfindcoupleforbracket.h"
#include <QtTest/QtTest>
#include <QStack>


testfindcoupleforbracket::testfindcoupleforbracket(QObject *parent) : QObject(parent) {}

void testfindcoupleforbracket::roundBracket() // №1.1. Круглая скобка
{
    QStringList code = {") ( { ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));

    int result = findCoupleForBracket(newBracket, brackets);
    QVERIFY2(result==0, "Error in function");
}

void testfindcoupleforbracket::squareBracket() // №1.2. Квадратная скобка
{
    QStringList code = {"] ( { ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));

    int result = findCoupleForBracket(newBracket, brackets);
    QVERIFY2(result==2, "Error in function");
}

void testfindcoupleforbracket::curlyBracket() // №1.3. Фигурная скобка
{
    QStringList code = {"} ( { ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));

    int result = findCoupleForBracket(newBracket, brackets);
    QCOMPARE(result, 1);
}

void testfindcoupleforbracket::multipleBracketsOfTheSameType() // №2. В стеке есть несколько (3-4) скобок того же типа
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = findCoupleForBracket(newBracket, brackets);
    QCOMPARE(result, 4);
}

void testfindcoupleforbracket::thereIsNoCouple() // №3. В стеке нет пары
{
    QStringList code = {"} ( [ ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = findCoupleForBracket(newBracket, brackets);
    QCOMPARE(result, -1);
}

void testfindcoupleforbracket::theStackIsEmpty() // №4. Стек пустой
{
    QStringList code = {")"};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;

    int result = findCoupleForBracket(newBracket, brackets);
    QCOMPARE(result, -1);
}

//Этот макрос заменяет main
QTEST_MAIN(testfindcoupleforbracket)
//Файл метаинформации, обязательно должен быть
// #include "testfindcoupleforbracket.moc"

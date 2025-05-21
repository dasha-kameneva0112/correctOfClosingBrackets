#include "testupdateconteinerofbrackets.h"
#include <QtTest/QtTest>
#include <QStack>

testupdateconteinerofbrackets::testupdateconteinerofbrackets(QObject *parent) : QObject(parent) {}

void testupdateconteinerofbrackets::addOpeningBracket() // №1. Добавление открывающей скобки
{
    QStringList code = {"("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 0);
}

void testupdateconteinerofbrackets::addCorrectCLosingBracket() // №2. Добавление закрывающей скобки (без ошибок)
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::addExcessiveClosingBracket() // №3. Добавление закрывающей скобки (ошибка - нет пары, лишняя закрывающая)
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::addSeveralExcessiveBrackets() // №4. В стеке есть несколько (3-4) скобок того же типа
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::incorrectOrderWithOneBracket() // №5.1. Неправильный порядок с предыдущей
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::incorrectOrderWithAllBrackets() // №5.2. Неправильный порядок с 3-4 всеми предыдущими
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::incorrectOrderWithSeveralBrackets() // №5.3. Неправильный порядок с 3-4 предыдущими (не всеми)
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::addMistakeIncorrectOrder() // №5.4. Добавление ошибки неправильного порядка (порядок уже изменен)
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::addMistakeInNotEmptyConteiner() // №6. Добавление ошибки в непустой контейнер
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

void testupdateconteinerofbrackets::complexTest() // №7. Корректная вложенность
{
    QStringList code = {") ( { ( [ ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));

    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, 4);
}

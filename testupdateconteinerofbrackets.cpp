#include "testupdateconteinerofbrackets.h"
#include <QStack>

testupdateconteinerofbrackets::testupdateconteinerofbrackets(QObject *parent) : QObject(parent) {}

void testupdateconteinerofbrackets::addOpeningBracket() // №1. Добавление открывающей скобки
{
    QStringList code = {"("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;

    QStack<bracket> exp_br;
    exp_br.push(newBracket);

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

void testupdateconteinerofbrackets::addCorrectCLosingBracket() // №2. Добавление закрывающей скобки (без ошибок)
{
    QStringList code = {") ("};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    QSet<mistake> mistakes;

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(brackets.isEmpty(), "Error in stack brackets");
}

void testupdateconteinerofbrackets::addExcessiveClosingBracket() // №3. Добавление закрывающей скобки (ошибка - нет пары, лишняя закрывающая)
{
    QStringList code = {") { ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    QSet<mistake> exp_mistakes;
    exp_mistakes.insert(mistake(bracket(code,0,0), ExcessiveClosingBracket));
    QStack<bracket> exp_br;
    exp_br.push(bracket(code, 0, 2));
    exp_br.push(bracket(code, 0, 4));

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

void testupdateconteinerofbrackets::addClosingBracketInEmptyContainer() // №4. Добавление закрывающей скобки в пустой контейнер (ошибка - нет пары, лишняя закрывающая)
{
    QStringList code = {")"};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;
    QSet<mistake> exp_mistakes;
    exp_mistakes.insert(mistake(bracket(code,0,0), ExcessiveClosingBracket));

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(brackets.isEmpty(), "Error in stack brackets");
}

void testupdateconteinerofbrackets::incorrectOrderWithOneBracket() // №5.1. Неправильный порядок с предыдущей (одной)
{
    QStringList code = {") ( ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    QStack<bracket> exp_br;
    bracket currentBr(bracket(code, 0, 4));
    currentBr.setOrder(false);
    exp_br.push(currentBr);

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

void testupdateconteinerofbrackets::incorrectOrderWithAllBrackets() // №5.2. Неправильный порядок с 3-4 всеми предыдущими
{
    QStringList code = {") ( [ [ {"};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));

    QStack<bracket> exp_br;
    bracket currentBr1(bracket(code, 0, 4));
    currentBr1.setOrder(false);
    exp_br.push(currentBr1);
    bracket currentBr2(bracket(code, 0, 6));
    currentBr2.setOrder(false);
    exp_br.push(currentBr2);
    bracket currentBr3(bracket(code, 0, 8));
    currentBr3.setOrder(false);
    exp_br.push(currentBr3);

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

void testupdateconteinerofbrackets::incorrectOrderWithSeveralBrackets() // №5.3. Неправильный порядок с 3-4 предыдущими (не всеми)
{
    QStringList code = {") [ { ( [ [ {"};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));
    brackets.push(bracket(code, 0, 12));

    QStack<bracket> exp_br;
    bracket currentBr1(bracket(code, 0, 2));
    exp_br.push(currentBr1);
    bracket currentBr2(bracket(code, 0, 4));
    exp_br.push(currentBr2);
    bracket currentBr3(bracket(code, 0, 8));
    currentBr3.setOrder(false);
    exp_br.push(currentBr3);
    bracket currentBr4(bracket(code, 0, 10));
    currentBr4.setOrder(false);
    exp_br.push(currentBr4);
    bracket currentBr5(bracket(code, 0, 12));
    currentBr5.setOrder(false);
    exp_br.push(currentBr5);

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

void testupdateconteinerofbrackets::addMistakeIncorrectOrder() // №5.4. Добавление ошибки неправильного порядка (порядок уже изменен)
{
    QStringList code = {"] ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    QSet<mistake> mistakes;
    bracket current_bracket(code, 0, 2);
    current_bracket.setOrder(false);
    brackets.push(current_bracket);

    QSet<mistake> exp_mistakes;
    exp_mistakes.insert(mistake(bracket(code,0,0), IncorrectOrderOfBrackets));

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(brackets.isEmpty(), "Error in stack brackets");
}

void testupdateconteinerofbrackets::addMistakeInNotEmptyConteiner() // №6. Добавление ошибки в непустой контейнер
{
    QStringList code = {"] { { )"};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    bracket current_bracket(code, 0, 6);
    QSet<mistake> mistakes;
    mistake current_mistake(current_bracket, ExcessiveClosingBracket);
    mistakes.insert(current_mistake);

    QSet<mistake> exp_mistakes;
    exp_mistakes.insert(current_mistake);
    exp_mistakes.insert(mistake(bracket(code,0,0), ExcessiveClosingBracket));

    QStack<bracket> exp_br;
    exp_br.push(bracket(code, 0, 2));
    exp_br.push(bracket(code, 0, 4));

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);  
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

void testupdateconteinerofbrackets::complexTest() // №7. Корректная вложенность
{
    QStringList code = {"] ( ["};
    bracket newBracket(code, 0, 0);

    QStack<bracket> brackets;
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    QStack<bracket> exp_br;
    exp_br.push(bracket(code, 0, 2));

    QSet<mistake> mistakes;

    int countOfMistakes = updateContainerOfBrackets(newBracket, brackets, mistakes);    
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(brackets==exp_br, "Error in stack brackets");
}

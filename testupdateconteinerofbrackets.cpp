#include "testupdateconteinerofbrackets.h"
#include <QStack>

testupdateconteinerofbrackets::testupdateconteinerofbrackets(QObject *parent) : QObject(parent) {}

void testupdateconteinerofbrackets::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<bracket>("newBracket");
    QTest::addColumn<QStack<bracket>>("brackets");
    QTest::addColumn<QSet<mistake>>("mistakes");
    QTest::addColumn<int>("countofmistakes");
    QTest::addColumn<QStack<bracket>>("exp_brackets");
    QTest::addColumn<QSet<mistake>>("exp_mistakes");

    //Создаем строки‐тесты и заполняем таблицу данными
    // №1. Добавление открывающей скобки
    QStringList code = {"("};
    bracket newBracket1(code, 0, 0);
    QStack<bracket> brackets;

    QStack<bracket> exp_brackets;
    exp_brackets.push(newBracket1);

    QSet<mistake> mistakes;
    QSet<mistake> exp_mistakes;
    QTest::newRow("addOpeningBracket") << newBracket1 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;

    // №2. Добавление закрывающей скобки (без ошибок)
    code = {") ("};
    bracket newBracket2(code, 0, 0);
    brackets.push(bracket(code, 0, 2));

    exp_brackets.pop(); // exp_brackets и exp_mistakes пустые

    QTest::newRow("addCorrectCLosingBracket") << newBracket2 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;

    brackets.pop();

    // №3. Добавление закрывающей скобки (ошибка - нет пары, лишняя закрывающая)
    code = {") { ["};
    bracket newBracket3(code, 0, 0);

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    exp_brackets.push(bracket(code, 0, 2));
    exp_brackets.push(bracket(code, 0, 4));
    exp_mistakes.insert(mistake(bracket(code,0,0), ExcessiveClosingBracket));

    QTest::newRow("addExcessiveClosingBracket") << newBracket3 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;

    brackets.pop();
    brackets.pop();
    exp_brackets.pop();
    exp_brackets.pop();
    exp_mistakes.clear();

    // №4. Добавление закрывающей скобки в пустой контейнер (ошибка - нет пары, лишняя закрывающая)
    code = {")"};
    bracket newBracket4(code, 0, 0);

    exp_mistakes.insert(mistake(bracket(code,0,0), ExcessiveClosingBracket));

    QTest::newRow("addClosingBracketInEmptyContainer") << newBracket4 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;

    exp_mistakes.clear();

    // №5.1. Неправильный порядок с предыдущей (одной)
    code = {") ( ["};
    bracket newBracket5(code, 0, 0);

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    bracket currentBr(bracket(code, 0, 4));
    currentBr.setOrder(false);
    exp_brackets.push(currentBr);

    QTest::newRow("incorrectOrderWithOneBracket") << newBracket5 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;

    brackets.pop();
    brackets.pop();
    exp_brackets.pop();

    // №5.2. Неправильный порядок с 3-4 всеми предыдущими
    code = {") ( [ [ {"};
    bracket newBracket6(code, 0, 0);
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));

    bracket currentBr1(bracket(code, 0, 4));
    currentBr1.setOrder(false);
    exp_brackets.push(currentBr1);
    bracket currentBr2(bracket(code, 0, 6));
    currentBr2.setOrder(false);
    exp_brackets.push(currentBr2);
    bracket currentBr3(bracket(code, 0, 8));
    currentBr3.setOrder(false);
    exp_brackets.push(currentBr3);

    QTest::newRow("incorrectOrderWithAllBrackets") << newBracket6 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;

    brackets.pop();
    brackets.pop();
    brackets.pop();
    brackets.pop();
    exp_brackets.pop();
    exp_brackets.pop();
    exp_brackets.pop();

    // №5.3. Неправильный порядок с 3-4 предыдущими (не всеми)
    code = {") [ { ( [ [ {"};
    bracket newBracket7(code, 0, 0);
    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));
    brackets.push(bracket(code, 0, 6));
    brackets.push(bracket(code, 0, 8));
    brackets.push(bracket(code, 0, 10));
    brackets.push(bracket(code, 0, 12));

    bracket currentBr4(bracket(code, 0, 2));
    exp_brackets.push(currentBr4);
    bracket currentBr5(bracket(code, 0, 4));
    exp_brackets.push(currentBr5);
    bracket currentBr6(bracket(code, 0, 8));
    currentBr6.setOrder(false);
    exp_brackets.push(currentBr6);
    bracket currentBr7(bracket(code, 0, 10));
    currentBr7.setOrder(false);
    exp_brackets.push(currentBr7);
    bracket currentBr8(bracket(code, 0, 12));
    currentBr8.setOrder(false);
    exp_brackets.push(currentBr8);
    QTest::newRow("incorrectOrderWithSeveralBrackets") << newBracket7 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;

    for(int i=0; i<6; i++)
        brackets.pop();
    for(int i=0; i<5; i++)
        exp_brackets.pop();

    // №5.4. Добавление ошибки неправильного порядка (порядок уже изменен)
    code = {"] ["};
    bracket newBracket8(code, 0, 0);

    bracket current_bracket(code, 0, 2);
    current_bracket.setOrder(false);
    brackets.push(current_bracket);

    exp_mistakes.insert(mistake(bracket(code,0,0), IncorrectOrderOfBrackets));
    QTest::newRow("addMistakeIncorrectOrder") << newBracket8 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;

    brackets.pop();
    exp_mistakes.clear();

    // №6. Добавление ошибки в непустой контейнер
    code = {"] { { )"};
    bracket newBracket9(code, 0, 0);

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    bracket current_bracket1(code, 0, 6);
    mistake current_mistake(current_bracket1, ExcessiveClosingBracket);
    mistakes.insert(current_mistake);

    exp_brackets.push(bracket(code, 0, 2));
    exp_brackets.push(bracket(code, 0, 4));

    exp_mistakes.insert(current_mistake);
    exp_mistakes.insert(mistake(bracket(code,0,0), ExcessiveClosingBracket));

    QTest::newRow("addMistakeInNotEmptyConteiner") << newBracket9 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;

    brackets.pop();
    brackets.pop();
    mistakes.clear();
    exp_mistakes.clear();
    exp_brackets.pop();
    exp_brackets.pop();


    // №7. Корректная вложенность
    code = {"] ( ["};
    bracket newBracket10(code, 0, 0);

    brackets.push(bracket(code, 0, 2));
    brackets.push(bracket(code, 0, 4));

    exp_brackets.push(bracket(code, 0, 2));

    QTest::newRow("complexTest") << newBracket10 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;
}

void testupdateconteinerofbrackets::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные
    QFETCH(bracket, newBracket);
    QFETCH(QStack<bracket>, brackets);
    QFETCH(QSet<mistake>, mistakes);
    QFETCH(int, countofmistakes);
    QFETCH(QStack<bracket>, exp_brackets);
    QFETCH(QSet<mistake>, exp_mistakes);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    int result = updateContainerOfBrackets(newBracket, brackets, mistakes);
    QCOMPARE(result, countofmistakes);

    QCOMPARE(brackets.size(), exp_brackets.size());
    if(brackets.size()==exp_brackets.size())
    {
        QStack<bracket>::const_iterator br = brackets.constBegin();
        QStack<bracket>::const_iterator e_br = exp_brackets.constBegin();
        bracket br1, br2;
        QByteArray mes = "Error in bracket - ";
        QByteArray messege;
        int number=1;
        for(br; br!=brackets.constEnd(); ++br)
        {
            br1 = (*br);
            br2 = (*e_br);
            messege = (mes+QString::number(number)).toUtf8();
            QVERIFY2(br1.getType()==br2.getType(), messege.constData());
            QVERIFY2(br1.getSide()==br2.getSide(), messege.constData());
            QVERIFY2(br1.getLine()==br2.getLine(), messege.constData());
            QVERIFY2(br1.getPosition()==br2.getPosition(), messege.constData());
            QVERIFY2(br1.getOrder()==br2.getOrder(), messege.constData());
            ++e_br;
            number++;
        }
    }
    QCOMPARE(mistakes.size(), exp_mistakes.size());
    if(mistakes.size()==exp_mistakes.size())
    {
        QSet<mistake>::const_iterator mt = mistakes.constBegin();
        QSet<mistake>::const_iterator e_mt = exp_mistakes.constBegin();
        mistake mt1, mt2;
        bracket br1, br2;
        QString mes = "Error in mistake - ";
        QByteArray messege;
        int number=1;
        for(mt; mt!=mistakes.constEnd(); ++mt)
        {
            mt1 = (*mt);
            mt2 = (*e_mt);
            messege = (mes+QString::number(number)).toUtf8();
            QVERIFY2(mt1.getType()==mt2.getType(), messege.constData());

            br1 = mt1.getBracket();
            br2 = mt2.getBracket();
            QVERIFY2(br1.getType()==br2.getType(), messege.constData());
            QVERIFY2(br1.getSide()==br2.getSide(), messege.constData());
            QVERIFY2(br1.getLine()==br2.getLine(), messege.constData());
            QVERIFY2(br1.getPosition()==br2.getPosition(), messege.constData());
            QVERIFY2(br1.getOrder()==br2.getOrder(), messege.constData());
            ++e_mt;
        }
    }
}




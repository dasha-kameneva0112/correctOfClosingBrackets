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


    exp_brackets.clear();


    // №2. Добавление закрывающей скобки (без ошибок)
    QStringList code_2 = {")"};
    bracket newBracket2(code_2, 0, 0);

    QStringList code2 = {"("};
    brackets.push(bracket(code2, 0, 0));
    QTest::newRow("addCorrectCLosingBracket") << newBracket2 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;


    brackets.clear();


    // №3. Добавление закрывающей скобки (ошибка - нет пары, лишняя закрывающая)
    QStringList code_3 = {")"};
    bracket newBracket3(code_3, 0, 0);

    QStringList code3 = {"{ ["};
    brackets.push(bracket(code3, 0, 0));
    brackets.push(bracket(code3, 0, 2));

    exp_brackets.push(bracket(code3, 0, 0));
    exp_brackets.push(bracket(code3, 0, 2));
    exp_mistakes.insert(mistake(newBracket3, ExcessiveClosingBracket));

    QTest::newRow("addExcessiveClosingBracket") << newBracket3 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;


    brackets.clear();
    exp_brackets.clear();
    exp_mistakes.clear();


    // №4. Добавление закрывающей скобки в пустой контейнер (ошибка - нет пары, лишняя закрывающая)
    QStringList code4 = {")"};
    bracket newBracket4(code4, 0, 0);
    exp_mistakes.insert(mistake(bracket(code4,0,0), ExcessiveClosingBracket));
    QTest::newRow("addClosingBracketInEmptyContainer") << newBracket4 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;


    exp_mistakes.clear();


    // №5.1. Неправильный порядок с предыдущей (одной)
    QStringList code_5 = {")"};
    bracket newBracket5(code_5, 0, 0);

    QStringList code5 = {"( ["};
    brackets.push(bracket(code5, 0, 0));
    brackets.push(bracket(code5, 0, 2));

    bracket currentBr(bracket(code5, 0, 2, false));
    exp_brackets.push(currentBr);
    QTest::newRow("incorrectOrderWithOneBracket") << newBracket5 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;


    brackets.clear();
    exp_brackets.clear();


    // №5.2. Неправильный порядок с 3-4 всеми предыдущими
    QStringList code_6 = {")"};
    bracket newBracket6(code_6, 0, 0);

    QStringList code6 = {"( [ [ {"};
    brackets.push(bracket(code6, 0, 0));
    brackets.push(bracket(code6, 0, 2));
    brackets.push(bracket(code6, 0, 4));
    brackets.push(bracket(code6, 0, 6));

    bracket currentBr1(bracket(code6, 0, 2, false));
    exp_brackets.push(currentBr1);
    bracket currentBr2(bracket(code6, 0, 4, false));
    exp_brackets.push(currentBr2);
    bracket currentBr3(bracket(code6, 0, 6, false));
    exp_brackets.push(currentBr3);
    QTest::newRow("incorrectOrderWithAllBrackets") << newBracket6 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;


    brackets.clear();
    exp_brackets.clear();


    // №5.3. Неправильный порядок с 3-4 предыдущими (не всеми)
    QStringList code_7 = {")"};
    bracket newBracket7(code_7, 0, 0);

    QStringList code7 = {"[ { ( [ [ {"};
    brackets.push(bracket(code7, 0, 0));
    brackets.push(bracket(code7, 0, 2));
    brackets.push(bracket(code7, 0, 4));
    brackets.push(bracket(code7, 0, 6));
    brackets.push(bracket(code7, 0, 8));
    brackets.push(bracket(code7, 0, 10));

    bracket currentBr4(bracket(code7, 0, 0));
    exp_brackets.push(currentBr4);
    bracket currentBr5(bracket(code7, 0, 2));
    exp_brackets.push(currentBr5);
    bracket currentBr6(bracket(code7, 0, 6, false));
    exp_brackets.push(currentBr6);
    bracket currentBr7(bracket(code7, 0, 8, false));
    exp_brackets.push(currentBr7);
    bracket currentBr8(bracket(code7, 0, 10, false));
    exp_brackets.push(currentBr8);
    QTest::newRow("incorrectOrderWithSeveralBrackets") << newBracket7 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;


    brackets.clear();
    exp_brackets.clear();


    // №5.4. Добавление ошибки неправильного порядка (порядок уже изменен)
    QStringList code_8 = {"]"};
    bracket newBracket8(code_8, 0, 0);

    QStringList code8 = {"["};
    bracket current_bracket(code8, 0, 0, false);
    brackets.push(current_bracket);

    exp_mistakes.insert(mistake(newBracket8, IncorrectOrderOfBrackets));
    QTest::newRow("addMistakeIncorrectOrder") << newBracket8 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;


    brackets.clear();
    exp_mistakes.clear();


    // №6. Добавление ошибки в непустой контейнер
    QStringList code_9 = {"]"};
    bracket newBracket9(code_9, 0, 0);

    QStringList code9 = {"{ { )"};
    brackets.push(bracket(code9, 0, 0));
    brackets.push(bracket(code9, 0, 2));

    bracket current_bracket1(code9, 0, 4);
    mistake current_mistake(current_bracket1, ExcessiveClosingBracket);
    mistakes.insert(current_mistake);

    exp_brackets.push(bracket(code9, 0, 0));
    exp_brackets.push(bracket(code9, 0, 2));

    exp_mistakes.insert(current_mistake);
    exp_mistakes.insert(mistake(newBracket9, ExcessiveClosingBracket));
    QTest::newRow("addMistakeInNotEmptyConteiner") << newBracket9 << brackets << mistakes << 1 << exp_brackets << exp_mistakes;


    brackets.clear();
    exp_brackets.clear();
    mistakes.clear();
    exp_mistakes.clear();


    // №7. Корректная вложенность
    QStringList code_10 = {"]"};
    bracket newBracket10(code_10, 0, 0);

    QStringList code10 = {"( ["};
    brackets.push(bracket(code10, 0, 0));
    brackets.push(bracket(code10, 0, 2));

    exp_brackets.push(bracket(code10, 0, 0));
    QTest::newRow("complexTest") << newBracket10 << brackets << mistakes << 0 << exp_brackets << exp_mistakes;

    brackets.clear();
    exp_brackets.clear();
    mistakes.clear();
    exp_mistakes.clear();
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

    int number=1;
    QByteArray message;
    if(brackets.size()==exp_brackets.size())
    {
        message = "Error in bracket - ";
        QStack<bracket>::const_iterator br;
        QStack<bracket>::const_iterator e_br = exp_brackets.constBegin();
        bracket br1, br2;
        for(br = brackets.constBegin(); br!=brackets.constEnd(); ++br)
        {
            br1 = (*br);
            br2 = (*e_br);
            message = message+(QString::number(number).toUtf8());
            QVERIFY2(br1.getType()==br2.getType(), message.constData());
            QVERIFY2(br1.getSide()==br2.getSide(), message.constData());
            QVERIFY2(br1.getLine()==br2.getLine(), message.constData());
            QVERIFY2(br1.getPosition()==br2.getPosition(), message.constData());
            QCOMPARE(br1.getOrder(),br2.getOrder());
            ++e_br;
            number++;
        }
    }

    // получаем избыточные
    QSet<mistake> temp1 = mistakes;
    temp1.subtract(exp_mistakes); // удаляет из mistakes элементы, которые есть в exp_mistakes

    // получаем недостающие
    QSet<mistake> temp2 = exp_mistakes;
    temp2.subtract(mistakes);  // удаляет из exp_mistakes элементы, которые есть в mistakes

    QString mes;
    QTextStream stream(&mes);
    stream << "Error in mistakes - ";
    mistake mt;
    bracket br;
    if(!(temp1.isEmpty()))
    {
        stream << "there are excessive elements(" << temp1.size() << "): ";

        QSet<mistake>::const_iterator it;
        for (it = temp1.constBegin(); it!=temp1.constEnd(); ++it)
        {
            mt = *it;
            br = mt.getBracket();

            stream << "#" << number++ << ". Type: " << mt.getType() << "; Bracket: (type - " << br.getType() << ", side - " << br.getSide() << ", line - "
                   << br.getLine() << ", position - " << br.getPosition() << ", order - " << QVariant(br.getOrder()).toString();
        }
    }
    if(!(temp2.isEmpty()))
    {
        stream << "there are missing elements(" << temp2.size() << "): ";

        QSet<mistake>::const_iterator it;
        for (it = temp2.constBegin(); it!=temp2.constEnd(); ++it)
        {
            mt = *it;
            br = mt.getBracket();

            stream << "#" << number++ << ". Type: " << mt.getType() << "; Bracket: (type - " << br.getType() << ", side - " << br.getSide() << ", line - "
                   << br.getLine() << ", position - " << br.getPosition() << ", order - " << QVariant(br.getOrder()).toString();
        }
    }
    message += mes.toUtf8();
    QVERIFY2(temp1.isEmpty() && temp2.isEmpty(), message.constData());
}





#include "testfindallincorrectusesofbrackets.h"
#include <QStack>

testfindallincorrectusesofbrackets::testfindallincorrectusesofbrackets(QObject *parent) : QObject(parent) {}

void testfindallincorrectusesofbrackets::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code"); ///< Исходный код для теста
    QTest::addColumn<QSet<mistake>>("mistakes"); ///< Найденные ошибки
    QTest::addColumn<errorininputdata>("error"); ///< Ошибки во входных данных
    QTest::addColumn<int>("countofmistakes"); ///< Ожидаемое количество ошибок
    QTest::addColumn<QSet<mistake>>("exp_mistakes"); ///< Ожидаемые ошибки
    QTest::addColumn<errorininputdata>("exp_error"); ///< Ожидаемые ошибки входных данных

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. нахождение скобок в обычном корректном коде
    /*!
     * \test Тест 1: Корректный код
     * Проверяет отсутствие ошибок в правильном коде
     */
    QStringList code1 = {
        "int main()",
        "{",
        "int x = (5+3);",
        "}"
    };
    QSet<mistake> mistakes;
    QSet<mistake> exp_mistakes;
    errorininputdata error;
    errorininputdata newError;
    QTest::newRow("findBracketInCorrectCode") << code1 << mistakes << error << 0 << exp_mistakes << newError;

    //№2. код с комментариями и константами, содержащие скобки (комплексный тест1)
    /*!
     * \test Тест 2: Код с комментариями и константами
     * Проверяет игнорирование скобок в комментариях и константах
     */
    QStringList code2 = {
        "int main()",
        "{",
        "// comment ((",
        "QString a = \"Hello, []]world!\"",
        "char b /* }comment */ = \'(\';"
        "}"
    };
    QTest::newRow("codeWithSkippingConstantsAndCommentsWithBrackets") << code2 << mistakes << error << 0 << exp_mistakes << newError;

    //№3. ошибка - лишняя закрывающая скобка
    /*!
     * \test Тест 3: Лишняя закрывающая скобка
     * Проверяет обнаружение избыточной закрывающей скобки
     */
    QStringList code3 = {
        "int main()",
        "{",
        "int x = (5+3);",
        "}",
        "}"
    };
    bracket current_bracket(code3, 4, 0);
    exp_mistakes.insert(mistake(current_bracket, ExcessiveClosingBracket));
    QTest::newRow("mistakeIsExcessiveClosingBracket") << code3 << mistakes << error << 1 << exp_mistakes << newError;

    mistakes.clear();
    exp_mistakes.clear();

    //№4. ошибка - незакрытая скобка
    /*!
     * \test Тест 4: Незакрытая скобка
     * Проверяет обнаружение незакрытой скобки
     */
    QStringList code4 = {
        "int main()",
        "{",
        "int x = (5+3);"
    };
    bracket current_bracket1(code4, 1, 0);
    exp_mistakes.insert(mistake(current_bracket1, UnclosedBracket));
    QTest::newRow("mistakeIsUnclosedBracket") << code4 << mistakes << error << 1 << exp_mistakes << newError;

    mistakes.clear();
    exp_mistakes.clear();

    //№5. ошибка - неправильный порядок
    /*!
     * \test Тест 5: Неправильный порядок скобок
     * Проверяет обнаружение некорректной последовательности скобок
     */
    QStringList code5 = {
        "int main()",
        "{",
        "int x = (5+3});"
    };
    bracket current_bracket2(code5, 2, 13);
    exp_mistakes.insert(mistake(current_bracket2, IncorrectOrderOfBrackets));
    QTest::newRow("mistakeIsIncorrectOrderOfBrackets") << code5 << mistakes << error << 1 << exp_mistakes << newError;

    mistakes.clear();
    exp_mistakes.clear();

    //№6. комплексный тест - комбинация всех ошибок
    /*!
     * \test Тест 6: Комбинация всех ошибок
     * Проверяет обнаружение нескольких типов ошибок
     */
    QStringList code6 = {
        "int main()",
        "{",
        "int x = [(5+3}; )",
        "}"
    };
    bracket current_bracket3(code6, 3, 0);
    bracket current_bracket4(code6, 2, 8, false);
    bracket current_bracket5(code6, 2, 16);
    exp_mistakes.insert(mistake(current_bracket3, ExcessiveClosingBracket));
    exp_mistakes.insert(mistake(current_bracket4, UnclosedBracket));
    exp_mistakes.insert(mistake(current_bracket5, IncorrectOrderOfBrackets));
    QTest::newRow("allMistakes") << code6 << mistakes << error << 3 << exp_mistakes << newError;

    mistakes.clear();
    exp_mistakes.clear();


    //№7. комплексный тест - несколько одинаковых ошибок
    /*!
     * \test Тест 7: Несколько одинаковых ошибок
     * Проверяет обнаружение нескольких ошибок одного типа
     */
    QStringList code7 = {
        "int main()",
        "{",
        "int x = [5+3)];",
        "}",
        "}"
    };
    bracket current_bracket6(code7, 2, 12);
    bracket current_bracket8(code7, 4, 0);
    exp_mistakes.insert(mistake(current_bracket6, ExcessiveClosingBracket));
    exp_mistakes.insert(mistake(current_bracket8, ExcessiveClosingBracket));
    QTest::newRow("severalSameMistakes") << code7 << mistakes << error << 2 << exp_mistakes << newError;

    mistakes.clear();
    exp_mistakes.clear();

    //№8. ошибка - незакрытая строковая константа
    /*!
     * \test Тест 8: Незакрытая строковая константа
     * Проверяет обнаружение незакрытой строковой константы
     */
    QStringList code8 = {
        "int main()",
        "{",
        "QString a = \"Hello, world! ;",
        "}"
    };
    newError.setType(UnclosedStringConst);
    newError.setLine(2);
    newError.setPos(12);
    QTest::newRow("errorIsUnclosedStringConst") << code8 << mistakes << error << 0 << exp_mistakes << newError;


    //№9. ошибка - незакрытая символьная константа
    /*!
     * \test Тест 9: Незакрытая символьная константа
     * Проверяет обнаружение незакрытой символьной константы
     */
    QStringList code9 = {
        "int main()",
        "{",
        "char b = \'H ;",
        "}" };
    newError.setType(UnclosedCharConst);
    newError.setLine(2);
    newError.setPos(9);
    QTest::newRow("errorIsUnclosedCharConst") << code9 << mistakes << error << 0 << exp_mistakes << newError;

    //№10. ошибка - незакрытый многострочный комментарий
    /*!
     * \test Тест 10: Незакрытый многострочный комментарий
     * Проверяет обнаружение незакрытого многострочного комментария
     */
    QStringList code10 = {
        "int main()",
        "{",
        "/* comment",
        "int x = (5 + 3); ",
        "}"  };
    newError.setType(UnclosedMultilineComment);
    newError.setLine(2);
    newError.setPos(1);
    QTest::newRow("errorIsUnclosedMultilineComment") << code10 << mistakes << error << 0 << exp_mistakes << newError;
}


void testfindallincorrectusesofbrackets::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные
    QFETCH(QStringList, code);
    QFETCH(QSet<mistake>, mistakes);
    QFETCH(errorininputdata, error);
    QFETCH(int, countofmistakes);
    QFETCH(QSet<mistake>, exp_mistakes);
    QFETCH(errorininputdata, exp_error);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    int result = findAllIncorrectUsesOfBrackets(code, mistakes, error);
    QCOMPARE(result, countofmistakes);

    // получаем избыточные
    QSet<mistake> temp1 = mistakes;
    temp1.subtract(exp_mistakes); // удаляет из mistakes элементы, которые есть в exp_mistakes

    // получаем недостающие
    QSet<mistake> temp2 = exp_mistakes;
    temp2.subtract(mistakes);  // удаляет из exp_mistakes элементы, которые есть в mistakes

    int number=1;
    QByteArray message;
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

    QCOMPARE(error.getType(), exp_error.getType());
    QCOMPARE(error.getLine(), exp_error.getLine());
    QCOMPARE(error.getPosition(), exp_error.getPosition());
}

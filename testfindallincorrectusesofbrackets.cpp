#include "testfindallincorrectusesofbrackets.h"
#include <QStack>

testfindallincorrectusesofbrackets::testfindallincorrectusesofbrackets(QObject *parent) : QObject(parent) {}

void testfindallincorrectusesofbrackets::findBracketInCorrectCode() //№1. нахождение скобок в обычном корректном коде
{
    QStringList code = {
        "int main()",
        "{",
        "int x = (5+3);",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::codeWithSkippingConstantsAndCommentsWithBrackets() //№2. код с комментариями и константами, содержащие скобки (комплексный тест1)
{
    QStringList code = {
        "int main()",
        "{",
        "// comment ((",
        "QString a = \"Hello, []]world!\"",
        "char b /\* }comment \*/ = \'(\';"
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::mistakeIsExcessiveClosingBracket() //№3. ошибка - лишняя закрывающая скобка
{
    QStringList code = {
        "int main()",
        "{",
        "int x = (5+3);",
        "}",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    QSet<mistake> exp_mistakes;
    bracket current_bracket(code, 4, 0);
    exp_mistakes.insert(mistake(current_bracket, ExcessiveClosingBracket));

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::mistakeIsUnclosedBracket() //№4. ошибка - незакрытая скобка
{
    QStringList code = {
        "int main()",
        "{",
        "int x = (5+3);"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    QSet<mistake> exp_mistakes;
    bracket current_bracket(code, 1, 0);
    exp_mistakes.insert(mistake(current_bracket, UnclosedBracket));

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::mistakeIsIncorrectOrderOfBrackets() //№5. ошибка - неправильный порядок
{
    QStringList code = {
        "int main()",
        "{",
        "int x = (5+3});"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    QSet<mistake> exp_mistakes;
    bracket current_bracket(code, 2, 13);
    exp_mistakes.insert(mistake(current_bracket, IncorrectOrderOfBrackets));

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==1, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::allMistakes() //№6. комплексный тест2 - комбинация всех ошибок
{
    QStringList code = {
        "int main()",
        "{",
        "int x = [(5+3}; )",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    QSet<mistake> exp_mistakes;
    bracket current_bracket1(code, 3, 0);
    bracket current_bracket2(code, 2, 8);
    bracket current_bracket3(code, 2, 13);
    exp_mistakes.insert(mistake(current_bracket1, ExcessiveClosingBracket));
    exp_mistakes.insert(mistake(current_bracket2, UnclosedBracket));
    exp_mistakes.insert(mistake(current_bracket3, IncorrectOrderOfBrackets));

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==3, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::severalSameMistakes() //№7. комплексный тест3 - несколько одинаковых ошибок
{
    QStringList code = {
        "int main()",
        "{",
        "int x = [5+3)];",
        "}",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    QSet<mistake> exp_mistakes;
    bracket current_bracket1(code, 2, 12);
    bracket current_bracket2(code, 2, 12);
    bracket current_bracket3(code, 4, 0);
    exp_mistakes.insert(mistake(current_bracket1, ExcessiveClosingBracket));
    exp_mistakes.insert(mistake(current_bracket2, IncorrectOrderOfBrackets));
    exp_mistakes.insert(mistake(current_bracket3, ExcessiveClosingBracket));

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==3, "Error in countOfMistakes");
    QVERIFY2(mistakes==exp_mistakes, "Error in mistakes");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindallincorrectusesofbrackets::errorIsUnclosedStringConst() //№8. ошибка - незакрытая строковая константа
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, world! ;",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    errorininputdata exp_error(UnclosedStringConst, 2, 12);

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(newError==exp_error, "Error in founded error");
}

void testfindallincorrectusesofbrackets::errorIsUnclosedCharConst() //№9. ошибка - незакрытая символьная константа
{
    QStringList code = {
        "int main()",
        "{",
        "char b = ‘H ;",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    errorininputdata exp_error(UnclosedCharConst, 3, 9);

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(newError==exp_error, "Error in founded error");
}

void testfindallincorrectusesofbrackets::errorIsUnclosedMultilineComment() //№10. ошибка - незакрытый многострочный комментарий
{
    QStringList code = {
        "int main()",
        "{",
        "/* comment",
        "int x = (5 + 3); ",
        "}"
    };
    QSet<mistake> mistakes;
    errorininputdata newError;

    errorininputdata exp_error(UnclosedMultilineComment, 3, 9);

    int countOfMistakes=findAllIncorrectUsesOfBrackets(code, mistakes, newError);
    QVERIFY2(countOfMistakes==0, "Error in countOfMistakes");
    QVERIFY2(mistakes.isEmpty(), "Error in mistakes");
    QVERIFY2(newError==exp_error, "Error in founded error");
}

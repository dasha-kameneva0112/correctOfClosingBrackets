#include "testfindnextbracket.h"
#include <QStack>

testfindnextbracket::testfindnextbracket(QObject *parent) : QObject(parent) {}

void testfindnextbracket::findBracketInBeginOfCode() //№1. нахождение скобки с начала кода
{
    QStringList code = {
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    int startLine=0;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==1, "Error in bracketIsFound");
    QVERIFY2(startLine==0, "Error in startLine");
    QVERIFY2(startPosition==8, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindnextbracket::skipOnelineCommentInCode() //№2. пропуск однострочного комментария
{
    QStringList code = {
        "// comment (",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    int startLine=0;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==1, "Error in bracketIsFound");
    QVERIFY2(startLine==1, "Error in startLine");
    QVERIFY2(startPosition==8, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindnextbracket::skipIncorrectOnelineCommentInCode() //№3. пропуск многострочного комментария (без ошибки)
{
    QStringList code = {
        "/\* (comment ",
        "comment2] \*/",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    int startLine=0;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==1, "Error in bracketIsFound");
    QVERIFY2(startLine==2, "Error in startLine");
    QVERIFY2(startPosition==8, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindnextbracket::skipMultilineCommentInCode() //№4. пропуск многострочного комментария (с ошибкой)
{
    QStringList code = {
        "/\* comment ",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    int startLine=0;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==-1, "Error in bracketIsFound");
    QVERIFY2(startLine==4, "Error in startLine");
    QVERIFY2(startPosition==0, "Error in startPosition");
    QVERIFY2(newError.getType()==UnclosedMultilineComment, "Error in type of error");
    QVERIFY2(newError.getLine()==0, "Error in number of error's line");
    QVERIFY2(newError.getPosition()==2, "Error in error's position");
}

void testfindnextbracket::skipIncorrectMultilineCommentInCode() //№5. пропуск строковой константы (без ошибки)
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, [world]]!\";",
        "}"
    };
    int startLine=2;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==1, "Error in bracketIsFound");
    QVERIFY2(startLine==3, "Error in startLine");
    QVERIFY2(startPosition==0, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindnextbracket::skipStringConstantInCode() //№6. пропуск строковой константы (с ошибкой)
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, [world]]! ;",
        "}"
    };
    int startLine=2;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==-1, "Error in bracketIsFound");
    QVERIFY2(startLine==2, "Error in startLine");
    QVERIFY2(startPosition==27, "Error in startPosition");
    QVERIFY2(newError.getType()==UnclosedStringConst, "Error in type of error");
    QVERIFY2(newError.getLine()==2, "Error in number of error's line");
    QVERIFY2(newError.getPosition()==12, "Error in error's position");
}

void testfindnextbracket::skipIncorrectStringConstantInCode() //№7. пропуск символьной коснтанты (без ошибки)
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'(\';",
        "}"
    };
    int startLine=2;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==1, "Error in bracketIsFound");
    QVERIFY2(startLine==3, "Error in startLine");
    QVERIFY2(startPosition==0, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindnextbracket::skipCharConstantInCode() //№8. пропуск символьной константы (с ошибкой)
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'( ;",
        "}"
    };
    int startLine=2;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==-1, "Error in bracketIsFound");
    QVERIFY2(startLine==2, "Error in startLine");
    QVERIFY2(startPosition==11, "Error in startPosition");
    QVERIFY2(newError.getType()==UnclosedCharConst, "Error in type of error");
    QVERIFY2(newError.getLine()==2, "Error in number of error's line");
    QVERIFY2(newError.getPosition()==9, "Error in error's position");
}

void testfindnextbracket::skipIncorrectCharConstantInCode() //№9. комплексный тест - комбинация комментариев и констант
{
    QStringList code = {
        "int main()",
        "{",
        "// comment",
        "/\* comment1",
        "comment2 \*/",
        "QString a = \"Hello, world!\";",
        "char b = \'H\';",
        "int x = (5+3);",
        "}"
    };
    int startLine=2;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==1, "Error in bracketIsFound");
    QVERIFY2(startLine==7, "Error in startLine");
    QVERIFY2(startPosition==8, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

void testfindnextbracket::bracketIsNotFound() //№10. скобка не найдена
{
    QStringList code = { "int x = 5 + 3;" };
    int startLine=0;
    int startPosition=0;
    errorininputdata newError;

    int bracketIsFound=findNextBracket(code, startLine, startPosition, newError);
    QVERIFY2(bracketIsFound==0, "Error in bracketIsFound");
    QVERIFY2(startLine==0, "Error in startLine");
    QVERIFY2(startPosition==12, "Error in startPosition");
    QVERIFY2(newError.getType()==NULL, "Error in type of error");
}

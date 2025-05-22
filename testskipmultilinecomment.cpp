#include "testskipmultilinecomment.h"
#include <QStack>

testskipmultilinecomment::testskipmultilinecomment(QObject *parent) : QObject(parent) {}

void testskipmultilinecomment::correctMultilineComment() //№1. корректный многострочный комментарий (на 2 строки)
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5;",
        "/* comment1",
        "comment2 */",
        "}"
    };
    int currentLine=3;
    int currentPosition=1;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==5, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskipmultilinecomment::correctMultilineCommentInPartOfLine() //№2. корректный многострочный комментарий (часть строки)
{
    QStringList code = {
        "int main()",
        "{",
        "int /* comment */ x = 5;",
        "}"
    };
    int currentLine=2;
    int currentPosition=5;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==16, "Error in currentPosition");
}

void testskipmultilinecomment::correctMultilineCommentInOneLine() //№3. корректный многострочный комментарий (на одну строку)
{
    QStringList code = {
        "int main()",
        "{",
        "/* comment */",
        "int x = 5;",
        "}"
    };
    int currentLine=2;
    int currentPosition=1;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==3, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskipmultilinecomment::unclosedMultilineComment() //№4. незакрытый комментарий
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5;",
        "/* comment ",
        "}"
    };
    int currentLine=3;
    int currentPosition=1;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==false, "Error in resultOfSkipping");
    QVERIFY2(currentLine==3, "Error in currentLine");
    QVERIFY2(currentPosition==1, "Error in currentPosition");
}

void testskipmultilinecomment::emptyMultilineComment() //№5. пустой комментарий
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5;",
        "/**/",
        "}"
    };
    int currentLine=3;
    int currentPosition=1;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==4, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskipmultilinecomment::escapedSlashAndAsteriskSymbol() //№6. экранированный слэш и звездочка
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5;",
        "/* *\\/ comment1 */",
        "}"
    };
    int currentLine=3;
    int currentPosition=1;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==4, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskipmultilinecomment::complexTest() //№7. комплексный тест
{
    QStringList code = {
        "int main()",
        "{",
        "int /* c*\\///om***me\\\\n*\\/t **/ x = 5;",
        "}"
    };
    int currentLine=2;
    int currentPosition=5;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==30, "Error in currentPosition");
}

void testskipmultilinecomment::multilineCommentInEndOfCode() //№8. комментарий в конце кода (файла)
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5;",
        "}",
        "/* comment */"
    };
    int currentLine=5;
    int currentPosition=1;
    bool resultOfSkipping=skipMultilineComment(code, currentLine, currentPosition);

    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==5, "Error in currentLine");
    QVERIFY2(currentPosition==12, "Error in currentPosition");
}

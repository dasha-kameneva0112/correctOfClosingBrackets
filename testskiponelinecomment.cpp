#include "testskiponelinecomment.h"
#include <QStack>

testskiponelinecomment::testskiponelinecomment(QObject *parent) : QObject(parent) {}


void testskiponelinecomment::standartOneLineComment() //№1. стандартный однострочный комментарий (в конце строки)
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5; // comment",
        "int y = 10;",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    skipOneLineComment(code, currentLine, currentPosition);
    QVERIFY2(currentLine==3, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskiponelinecomment::onelineCommentInSeveralLine() //№2. стандартный однострочный комментарий (в 2-3 строки)
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5; // comment \\",
        "comment2 \\",
        "comment3 ",
        "int y = 10;",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    skipOneLineComment(code, currentLine, currentPosition);
    QVERIFY2(currentLine==5, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskiponelinecomment::escapedSlashInEndOfOnelineComment() //№3. экранированный слэш в конце комментария
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5; // comment \\\\\\\\",
        "int y = 10;",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    skipOneLineComment(code, currentLine, currentPosition);
    QVERIFY2(currentLine==4, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskiponelinecomment::emptyOnelineComment() //№4. пустой комментарий
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5; //",
        "int y = 10;",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    skipOneLineComment(code, currentLine, currentPosition);
    QVERIFY2(currentLine==3, "Error in currentLine");
    QVERIFY2(currentPosition==0, "Error in currentPosition");
}

void testskiponelinecomment::onelineCommentInEndOfCode() //№5. комментарий в конце кода
{
    QStringList code = {
        "int main()",
        "{",
        "int x = 5;",
        "}// comment"
    };
    int currentLine=3;
    int currentPosition=2;

    skipOneLineComment(code, currentLine, currentPosition);
    QVERIFY2(currentLine==3, "Error in currentLine");
    QVERIFY2(currentPosition==11, "Error in currentPosition");
}

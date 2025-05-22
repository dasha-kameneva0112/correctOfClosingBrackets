#include "testskipcharconstant.h"

testskipcharconstant::testskipcharconstant(QObject *parent) : QObject(parent) {}

void testskipcharconstant::simpleClosingCharConst() //№1. простая символьная константа
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'H\';",
        "}"
    };
    int currentLine=2;
    int currentPosition=9;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==11, "Error in currentPosition");
}

void testskipcharconstant::escapedQuotationMarkInsideCharConst() //№2. экранированная кавычка
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'\\\'\';",
        "}"
    };
    int currentLine=2;
    int currentPosition=9;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==12, "Error in currentPosition");
}

void testskipcharconstant::unclosedCharConst() //№3. незакрытая константа
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'H;",
        "}"
    };
    int currentLine=2;
    int currentPosition=9;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==false, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==9, "Error in currentPosition");
}

void testskipcharconstant::emptyCharConst() //№4. пустая константа
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'\';",
        "}"
    };
    int currentLine=2;
    int currentPosition=9;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==10, "Error in currentPosition");
}

void testskipcharconstant::escapedSlashInsideCharConst() //№5. экранированный слэш
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'\\\\\';",
        "}"
    };
    int currentLine=2;
    int currentPosition=9;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==12, "Error in currentPosition");
}

void testskipcharconstant::incorrectEscapedSlashInsideCharConst() //№6. неправильное экранирование слэша (ошибка)
{
    QStringList code = {
        "int main()",
        "{",
        "char a = \'\\\';",
        "}"
    };
    int currentLine=2;
    int currentPosition=9;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==false, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==9, "Error in currentPosition");
}

#include "testskipstringconstant.h"

testskipstringconstant::testskipstringconstant(QObject *parent) : QObject(parent) {}

void testskipstringconstant::simpleClosingStringConst() //№1. простая строковая закрывающаяся константа
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, world!\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==26, "Error in currentPosition");
}

void testskipstringconstant::escapedQuotationMarkInsideStringConst() //№2. экранированная кавычка
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, \\\"world!\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==28, "Error in currentPosition");
}

void testskipstringconstant::escapedSlashInsideStringConst() //№3. экранированный слэш
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, world!\\\\\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==28, "Error in currentPosition");
}

void testskipstringconstant::unclosedStringConst() //№4. незакрытая строковая константа
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, world! ;",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==false, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==12, "Error in currentPosition");
}

void testskipstringconstant::IncorrectEscapedQuotationMarkInsideStringConst() //№5. экранированная кавычка (ошибка)
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, world! \\\\\\\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==false, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==12, "Error in currentPosition");
}

void testskipstringconstant::multilineStringConst() //№6. перенос строковой константы на другую строку
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, \\",
        "world!\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==3, "Error in currentLine");
    QVERIFY2(currentPosition==6, "Error in currentPosition");
}

void testskipstringconstant::emptyStringConst() //№7. пустая строковая константа
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==true, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==13, "Error in currentPosition");
}

void testskipstringconstant::incorrectMultilineStringConst() //№8. перенос строковой константы без слэша (ошибка)
{
    QStringList code = {
        "int main()",
        "{",
        "QString a = \"Hello, ",
        "world!\";",
        "}"
    };
    int currentLine=2;
    int currentPosition=12;

    bool resultOfSkipping=skipStringConstant(code, currentLine, currentPosition);
    QVERIFY2(resultOfSkipping==false, "Error in resultOfSkipping");
    QVERIFY2(currentLine==2, "Error in currentLine");
    QVERIFY2(currentPosition==12, "Error in currentPosition");
}

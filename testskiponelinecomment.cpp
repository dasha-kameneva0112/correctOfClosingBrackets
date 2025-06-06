#include "testskiponelinecomment.h"
#include <QStack>

testskiponelinecomment::testskiponelinecomment(QObject *parent) : QObject(parent) {}

void testskiponelinecomment::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("currentLine");
    QTest::addColumn<int>("currentPosition");
    QTest::addColumn<int>("exp_currentLine");
    QTest::addColumn<int>("exp_currentPosition");

    //Создаем строки‐тесты и заполняем таблицу данными 

    //№1. стандартный однострочный комментарий (в конце строки)
    QStringList test_code1 = {
        "int main()",
        "{",
        "int x = 5; // comment",
        "int y = 10;",
        "}"
    };
    QTest::newRow("standartOneLineComment") << test_code1 << 2 << 12 << 3 << 0;

    //№2. стандартный однострочный комментарий (в 2-3 строки)
    QStringList test_code2 = {
        "int main()",
        "{",
        "int x = 5; // comment \\",
        "comment2 \\",
        "comment3 ",
        "int y = 10;",
        "}"
    };
    QTest::newRow("onelineCommentInSeveralLine") << test_code2 << 2 << 12 << 5 << 0;

    //№3. экранированный слэш в конце комментария
    QStringList test_code3 = {
        "int main()",
        "{",
        "int x = 5; // comment \\\\\\\\",
        "int y = 10;",
        "}"
    };
    QTest::newRow("escapedSlashInEndOfOnelineComment") << test_code3 << 2 << 12 << 4 << 0;
    
    //№4. пустой комментарий
    QStringList test_code4 = {
        "int main()",
        "{",
        "int x = 5; //",
        "int y = 10;",
        "}"
    };
    QTest::newRow("emptyOnelineComment") << test_code4 << 2 << 12 << 3 << 0;
    
    //№5. комментарий в конце кода
    QStringList test_code5 = {
        "int main()",
        "{",
        "int x = 5;",
        "}// comment"
    };
    QTest::newRow("onelineCommentInEndOfCode") << test_code5 << 3 << 2 << 3 << 11;
}

void testskiponelinecomment::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные 
    QFETCH(QStringList, code);
    QFETCH(int, currentLine);
    QFETCH(int, currentPosition);
    QFETCH(int, exp_currentLine);
    QFETCH(int, exp_currentPosition);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    skipOneLineComment(code, currentLine, currentPosition);
    QCOMPARE(currentLine, exp_currentLine);
    QCOMPARE(currentPosition, exp_currentPosition);
}

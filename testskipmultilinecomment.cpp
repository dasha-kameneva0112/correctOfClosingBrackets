#include "testskipmultilinecomment.h"
#include <QStack>

testskipmultilinecomment::testskipmultilinecomment(QObject *parent) : QObject(parent) {}


void testskipmultilinecomment::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("currentLine");
    QTest::addColumn<int>("currentPosition");
    QTest::addColumn<bool>("resultofskipping");
    QTest::addColumn<int>("exp_currentLine");
    QTest::addColumn<int>("exp_currentPosition");

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. корректный многострочный комментарий (на 2 строки)
    QStringList test_code1 ={
        "int main()",
        "{",
        "int x = 5;",
        "/* comment1",
        "comment2 */",
        "}"
    };
    QTest::newRow("correctMultilineComment") << test_code1 << 3 << 1 << true << 4 << 10;

    //№2. корректный многострочный комментарий (часть строки)
    QStringList test_code2 = {
        "int main()",
        "{",
        "int /* comment */ x = 5;",
        "}"
    };
    QTest::newRow("correctMultilineCommentInPartOfLine") << test_code2 << 2 << 5 << true << 2 << 16;

    //№3. корректный многострочный комментарий (на одну строку)
    QStringList test_code3 ={
        "int main()",
        "{",
        "/* comment */",
        "int x = 5;",
        "}"
    };
    QTest::newRow("correctMultilineCommentInOneLine") << test_code3 << 2 << 1 << true << 2 << 12;

    //№4. незакрытый комментарий
    QStringList test_code4 = {
        "int main()",
        "{",
        "int x = 5;",
        "/* comment ",
        "}"
    };
    QTest::newRow("unclosedMultilineComment") << test_code4 << 3 << 1 << false << 3 << 1;

    //№5. пустой комментарий
    QStringList test_code5 = {
        "int main()",
        "{",
        "int x = 5;",
        "/**/",
        "}"
    };
    QTest::newRow("emptyMultilineComment") << test_code5 << 3 << 1 << true << 3 << 3;


    //№6. экранированный слэш и звездочка
    QStringList test_code6 = {
        "int main()",
        "{",
        "int x = 5;",
        "/* *\\/ comment1 */",
        "}"
    };
    QTest::newRow("escapedSlashAndAsteriskSymbol") << test_code6 << 3 << 1 << true << 3 << 17;

    //№7. комплексный тест
    QStringList test_code7 = {
        "int main()",
        "{",
        "int /* c*\\///om***me\\\\n*\\/t **/ x = 5;",
        "}"
    };
    QTest::newRow("complexTest") << test_code7 << 2 << 5 << true << 2 << 30;

    //№8. комментарий в конце кода (файла)
    QStringList test_code8 = {
        "int main()",
        "{",
        "int x = 5;",
        "}",
        "/* comment */"
    };
    QTest::newRow("emptyStringConst") << test_code8 << 4 << 1 << true << 4 << 12;
}

void testskipmultilinecomment::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные
    QFETCH(QStringList, code);
    QFETCH(int, currentLine);
    QFETCH(int, currentPosition);
    QFETCH(bool, resultofskipping);
    QFETCH(int, exp_currentLine);
    QFETCH(int, exp_currentPosition);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    bool result = skipMultilineComment(code, currentLine, currentPosition);
    QCOMPARE(result, resultofskipping);
    QCOMPARE(currentLine, exp_currentLine);
    QCOMPARE(currentPosition, exp_currentPosition);
}


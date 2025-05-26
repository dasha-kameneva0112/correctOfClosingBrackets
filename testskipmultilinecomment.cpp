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
    QStringList test_code ={
        "int main()",
        "{",
        "int x = 5;",
        "/* comment1",
        "comment2 */",
        "}" };
    QTest::newRow("correctMultilineComment") << test_code << 3 << 1 << true << 4 << 10;

    //№2. корректный многострочный комментарий (часть строки)
    test_code = {
        "int main()",
        "{",
        "int /* comment */ x = 5;",
        "}"
    };
    QTest::newRow("correctMultilineCommentInPartOfLine") << test_code << 2 << 5 << true << 2 << 16;

    //№3. корректный многострочный комментарий (на одну строку)
    test_code ={
        "int main()",
        "{",
        "/* comment */",
        "int x = 5;",
        "}"
    };
    QTest::newRow("correctMultilineCommentInOneLine") << test_code << 2 << 1 << true << 2 << 12;

    //№4. незакрытый комментарий
    test_code = {
        "int main()",
        "{",
        "int x = 5;",
        "/* comment ",
        "}"
    };
    QTest::newRow("unclosedMultilineComment") << test_code << 3 << 1 << false << 3 << 1;

    //№5. пустой комментарий
    test_code = {
        "int main()",
        "{",
        "int x = 5;",
        "/**/",
        "}"
    };
    QTest::newRow("emptyMultilineComment") << test_code << 3 << 1 << true << 3 << 3;


    //№6. экранированный слэш и звездочка
    test_code = {
        "int main()",
        "{",
        "int x = 5;",
        "/* *\\/ comment1 */",
        "}"
    };
    QTest::newRow("escapedSlashAndAsteriskSymbol") << test_code << 3 << 1 << true << 3 << 17;

    //№7. комплексный тест
    test_code = {
        "int main()",
        "{",
        "int /* c*\\///om***me\\\\n*\\/t **/ x = 5;",
        "}"
    };
    QTest::newRow("complexTest") << test_code << 2 << 5 << true << 2 << 30;

    //№8. комментарий в конце кода (файла)
    test_code = {
        "int main()",
        "{",
        "int x = 5;",
        "}",
        "/* comment */"
    };
    QTest::newRow("emptyStringConst") << test_code << 4 << 1 << true << 4 << 12;
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


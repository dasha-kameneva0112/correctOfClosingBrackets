#include "testfindnextbracket.h"
#include <QStack>

testfindnextbracket::testfindnextbracket(QObject *parent) : QObject(parent) {}

void complexTest(); //№9. комплексный тест - комбинация комментариев и констант
void bracketIsNotFound(); //№10. скобка не найдена

void testfindnextbracket::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("startLine");
    QTest::addColumn<int>("startPosition");
    QTest::addColumn<errorininputdata>("error");
    QTest::addColumn<int>("bracketisfound");
    QTest::addColumn<int>("exp_startLine");
    QTest::addColumn<int>("exp_startPosition");
    QTest::addColumn<errorininputdata>("exp_error");

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. нахождение скобки с начала кода
    QStringList test_code ={
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}" };
    errorininputdata error;
    errorininputdata newError;
    QTest::newRow("findBracketInBeginOfCode") << test_code << 0 << 0 << error << 1 << 0 << 8 << newError;

    //№2. пропуск однострочного комментария
    test_code = {
        "// comment (",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}" };
    QTest::newRow("skipOnelineCommentInCode") << test_code << 0 << 0 << error << 1 << 1 << 8 << newError;

    //№3. пропуск многострочного комментария (без ошибки)
    test_code = {
        "/\* (comment ",
        "comment2] \*/",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}" };
    QTest::newRow("skipMultilineCommentInCode") << test_code << 0 << 0 << error << 1 << 2 << 8 << newError;

    //№4. пропуск многострочного комментария (с ошибкой)
    test_code = {
        "/\* comment ",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}" };
    newError.setType(UnclosedMultilineComment);
    newError.setLine(0);
    newError.setPos(1);
    QTest::newRow("skipIncorrectMultilineCommentInCode") << test_code << 0 << 0 << error << -1 << 0 << 1 << newError;

    //№5. пропуск строковой константы (без ошибки)
    test_code = {
        "int main()",
        "{",
        "QString a = \"Hello, [world]]!\";",
        "}" };
    newError.setType(NoError);
    newError.setLine(-1);
    newError.setPos(-1);
    QTest::newRow("skipStringConstantInCode") << test_code << 2 << 0 << error << 1 << 3 << 0 << newError;

    //№6. пропуск строковой константы (с ошибкой)
    test_code = {
        "int main()",
        "{",
        "QString a = \"Hello, [world]]! ;",
        "}" };
    newError.setType(UnclosedStringConst);
    newError.setLine(2);
    newError.setPos(12);
    QTest::newRow("skipIncorrectStringConstantInCode") << test_code << 2 << 0 << error << -1 << 2 << 12 << newError;

    //№7. пропуск символьной коснтанты (без ошибки)
    test_code = {
        "int main()",
        "{",
        "char a = \'(\';",
        "}" };
    newError.setType(NoError);
    newError.setLine(-1);
    newError.setPos(-1);
    QTest::newRow("skipCharConstantInCode") << test_code << 2 << 0 << error << 1 << 3 << 0 << newError;

    //№8. пропуск символьной константы (с ошибкой)
    test_code={
        "int main()",
        "{",
        "char a = \'( ;",
        "}"
    };
    newError.setType(UnclosedCharConst);
    newError.setLine(2);
    newError.setPos(9);
    QTest::newRow("skipIncorrectCharConstantInCode") << test_code << 2 << 0 << error << -1 << 2 << 9 << newError;

    //№9. комплексный тест - комбинация комментариев и констант
    test_code = {
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
    newError.setType(NoError);
    newError.setLine(-1);
    newError.setPos(-1);
    QTest::newRow("complexTest") << test_code << 2 << 0 << error << 1 << 7 << 8 << newError;

    //№10. скобка не найдена
    test_code = { "int x = 5 + 3;" };
    QTest::newRow("notFoundBracket") << test_code << 0 << 0 << error << 0 << 0 << 13 << newError;
}

void testfindnextbracket::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные
    QFETCH(QStringList, code);
    QFETCH(int, startLine);
    QFETCH(int, startPosition);
    QFETCH(errorininputdata, error);
    QFETCH(int, bracketisfound);
    QFETCH(int, exp_startLine);
    QFETCH(int, exp_startPosition);
    QFETCH(errorininputdata, exp_error);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    int result = findNextBracket(code, startLine, startPosition, error);
    QCOMPARE(result, bracketisfound);
    QCOMPARE(startLine, exp_startLine);
    QCOMPARE(startPosition, exp_startPosition);
    QCOMPARE(error.getType(), exp_error.getType());
    QCOMPARE(error.getLine(), exp_error.getLine());
    QCOMPARE(error.getPosition(), exp_error.getPosition());
}

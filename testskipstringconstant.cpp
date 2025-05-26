#include "testskipstringconstant.h"

testskipstringconstant::testskipstringconstant(QObject *parent) : QObject(parent) {}

void testskipstringconstant::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("currentLine");
    QTest::addColumn<int>("currentPosition");
    QTest::addColumn<bool>("resultofskipping");
    QTest::addColumn<int>("exp_currentLine");
    QTest::addColumn<int>("exp_currentPosition");

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. простая строковая закрывающаяся константа
    QStringList test_code ={
        "int main()",
        "{",
        "QString a = \"Hello, world!\";",
        "}"  };
    QTest::newRow("simpleClosingStringConst") << test_code << 2 << 12 << true << 2 << 26;

    //№2. экранированная кавычка
    test_code ={
        "int main()",
        "{",
        "QString a = \"Hello, \\\"world!\";",
        "}" };
    QTest::newRow("escapedQuotationMarkInsideStringConst") << test_code << 2 << 12 << true << 2 << 28;

    //№3. экранированный слэш
    test_code ={
        "int main()",
        "{",
        "QString a = \"Hello, world!\\\\\";",
        "}" };
    QTest::newRow("escapedSlashInsideStringConst") << test_code << 2 << 12 << true << 2 << 28;

    //№4. незакрытая строковая константа
    test_code = {
        "int main()",
        "{",
        "QString a = \"Hello, world! ;",
        "}" };
    QTest::newRow("unclosedStringConst") << test_code << 2 << 12 << false << 2 << 12;

    //№5. экранированная кавычка (ошибка)
    test_code = {
        "int main()",
        "{",
        "QString a = \"Hello, world! \\\\\\\";",
        "}" };
    QTest::newRow("IncorrectEscapedQuotationMarkInsideStringConst") << test_code << 2 << 12 << false << 2 << 12;

    //№6. перенос строковой константы на другую строку
    test_code ={
        "int main()",
        "{",
        "QString a = \"Hello, \\",
        "world!\";",
        "}" };
    QTest::newRow("multilineStringConst") << test_code << 2 << 12 << true << 3 << 6;

    //№7. пустая строковая константа
    test_code = {
        "int main()",
        "{",
        "QString a = \"\";",
        "}"  };
    QTest::newRow("emptyStringConst") << test_code << 2 << 12 << true << 2 << 13;

    //№8. перенос строковой константы без слэша (ошибка)
    test_code = {
        "int main()",
        "{",
        "QString a = \"Hello, ",
        "world!\";",
        "}" };
    QTest::newRow("incorrectMultilineStringConst") << test_code << 2 << 12 << false << 2 << 12;
}

void testskipstringconstant::add()
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
    bool result = skipStringConstant(code, currentLine, currentPosition);
    QCOMPARE(result, resultofskipping);
    QCOMPARE(currentLine, exp_currentLine);
    QCOMPARE(currentPosition, exp_currentPosition);
}

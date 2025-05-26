#include "testskipcharconstant.h"

testskipcharconstant::testskipcharconstant(QObject *parent) : QObject(parent) {}

void testskipcharconstant::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("currentLine");
    QTest::addColumn<int>("currentPosition");
    QTest::addColumn<bool>("resultofskipping");
    QTest::addColumn<int>("exp_currentLine");
    QTest::addColumn<int>("exp_currentPosition");

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. простая символьная константа
    QStringList test_code ={
        "int main()",
        "{",
        "char a = \'H\';",
        "}"
    };
    QTest::newRow("simpleClosingCharConst") << test_code << 2 << 9 << true << 2 << 11;

    //№2. экранированная кавычка
    test_code ={
        "int main()",
        "{",
        "char a = \'\\\'\';",
        "}"
    };
    QTest::newRow("escapedQuotationMarkInsideCharConst") << test_code << 2 << 9 << true << 2 << 12;

    //№3. незакрытая константа
    test_code ={
        "int main()",
        "{",
        "char a = \'H;",
        "}" };
    QTest::newRow("unclosedCharConst") << test_code << 2 << 9 << false << 2 << 9;

    //№4. пустая константа
    test_code ={
        "int main()",
        "{",
        "char a = \'\';",
        "}"  };
    QTest::newRow("emptyCharConst") << test_code << 2 << 9 << true << 2 << 10;

    //№5. экранированный слэш
    test_code ={
        "int main()",
        "{",
        "char a = \'\\\\\';",
        "}" };
    QTest::newRow("escapedSlashInsideCharConst") << test_code << 2 << 9 << true << 2 << 12;

    //№6. неправильное экранирование слэша (ошибка)
    test_code ={
        "int main()",
        "{",
        "char a = \'\\\';",
        "}" };
    QTest::newRow("incorrectEscapedSlashInsideCharConst") << test_code << 2 << 9 << false << 2 << 9;
}


void testskipcharconstant::add()
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
    bool result = skipCharConstant(code, currentLine, currentPosition);
    QCOMPARE(result, resultofskipping);
    QCOMPARE(currentLine, exp_currentLine);
    QCOMPARE(currentPosition, exp_currentPosition);
}

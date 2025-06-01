#include "testconstructorbracket.h"

testconstructorbracket::testconstructorbracket(QObject *parent) : QObject(parent) {}

void testconstructorbracket::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("line");
    QTest::addColumn<int>("pos");
    QTest::addColumn<bool>("order");
    QTest::addColumn<BracketType>("exp_type");
    QTest::addColumn<BracketSide>("exp_side");
    QTest::addColumn<int>("exp_line");
    QTest::addColumn<int>("exp_pos");
    QTest::addColumn<bool>("exp_order");

    // №1. Открывающая круглая скобка
    QStringList code1 = {"("};
    QTest::newRow("openingRoundBracket") << code1 << 0 << 0 << true << Round << Opening << 0 << 0 << true;

    // №2. Открывающая фигурная скобка
    QStringList code2 = {"{"};
    QTest::newRow("openingCurlyBracket") << code2 << 0 << 0 << true << Curly << Opening << 0 << 0 << true;

    // №3. Открывающая квадратная скобка
    QStringList code3 = {"["};
    QTest::newRow("openingSquareBracket") << code3 << 0 << 0 << true << Square << Opening << 0 << 0 << true;

    // №4. Закрывающая круглая скобка
    QStringList code4 = {")"};
    QTest::newRow("closingRoundBracket") << code4 << 0 << 0 << true << Round << Closing << 0 << 0 << true;

    // №5. Закрывающая фигурная скобка
    QStringList code5 = {"}"};
    QTest::newRow("closingCurlyBracket") << code5 << 0 << 0 << true << Curly << Closing << 0 << 0 << true;

    // №6. Закрывающая квадратная скобка
    QStringList code6 = {"]"};
    QTest::newRow("closingCurlyBracket") << code6 << 0 << 0 << true << Square << Closing << 0 << 0 << true;

    // №7. неправильные порядок
    QStringList code7 = {"("};
    QTest::newRow("IncorrectOrder") << code7 << 0 << 0 << false << Round << Opening << 0 << 0 << false;

    // №8. правильные порядок
    QStringList code8 = {"("};
    QTest::newRow("CorrectOrder") << code8 << 0 << 0 << true << Round << Opening << 0 << 0 << true;

    // №9. скобка не в начале кода
    QStringList code9 = {"} ( [ ( [ ("};
    QTest::newRow("bracketisnotinbeginofcode") << code9 << 0 << 4 << true << Square << Opening << 0 << 4 << true;
}

void testconstructorbracket::add()
{
    // объект тестируемого класса,чтобы было откуда вызывать методы
    // изымает из таблицы данные в указанные переменные
    QFETCH(QStringList, code);
    QFETCH(int, line);
    QFETCH(int, pos);
    QFETCH(bool, order);
    QFETCH(BracketType, exp_type);
    QFETCH(BracketSide, exp_side);
    QFETCH(int, exp_line);
    QFETCH(int, exp_pos);
    QFETCH(bool, exp_order);

    // Вызываем метод класса и сравниваем полученное значение с ожидаемым
    bracket newBracket(code, line, pos, order);
    QCOMPARE(newBracket.getType(), exp_type);
    QCOMPARE(newBracket.getSide(), exp_side);
    QCOMPARE(newBracket.getLine(), exp_line);
    QCOMPARE(newBracket.getPosition(), exp_pos);
    QCOMPARE(newBracket.getOrder(), exp_order);
}

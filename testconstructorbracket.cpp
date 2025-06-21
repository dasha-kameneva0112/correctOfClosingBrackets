#include "testconstructorbracket.h"

testconstructorbracket::testconstructorbracket(QObject *parent) : QObject(parent) {}

void testconstructorbracket::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code"); ///< Исходный код для теста
    QTest::addColumn<int>("line"); ///< Номер строки со скобкой
    QTest::addColumn<int>("pos"); ///< Позиция скобки в строке
    QTest::addColumn<bool>("order"); ///< Флаг правильного порядка
    QTest::addColumn<BracketType>("exp_type"); ///< Ожидаемый тип скобки
    QTest::addColumn<BracketSide>("exp_side"); ///< Ожидаемое направление скобки
    QTest::addColumn<int>("exp_line"); ///< Ожидаемый номер строки
    QTest::addColumn<int>("exp_pos"); ///< Ожидаемая позиция
    QTest::addColumn<bool>("exp_order"); ///< Ожидаемый флаг порядка

    // №1. Открывающая круглая скобка
    /*!
     * \test Тест 1: Открывающая круглая скобка
     * Проверяет корректное создание объекта для '('
     */
    QStringList code1 = {"("};
    QTest::newRow("openingRoundBracket") << code1 << 0 << 0 << true << Round << Opening << 0 << 0 << true;

    // №2. Открывающая фигурная скобка
    /*!
     * \test Тест 2: Открывающая фигурная скобка
     * Проверяет корректное создание объекта для '{'
     */
    QStringList code2 = {"{"};
    QTest::newRow("openingCurlyBracket") << code2 << 0 << 0 << true << Curly << Opening << 0 << 0 << true;

    // №3. Открывающая квадратная скобка
    /*!
     * \test Тест 3: Открывающая квадратная скобка
     * Проверяет корректное создание объекта для '['
     */
    QStringList code3 = {"["};
    QTest::newRow("openingSquareBracket") << code3 << 0 << 0 << true << Square << Opening << 0 << 0 << true;

    // №4. Закрывающая круглая скобка
    /*!
     * \test Тест 4: Закрывающая круглая скобка
     * Проверяет корректное создание объекта для ')'
     */
    QStringList code4 = {")"};
    QTest::newRow("closingRoundBracket") << code4 << 0 << 0 << true << Round << Closing << 0 << 0 << true;

    // №5. Закрывающая фигурная скобка
    /*!
     * \test Тест 5: Закрывающая фигурная скобка
     * Проверяет корректное создание объекта для '}'
     */
    QStringList code5 = {"}"};
    QTest::newRow("closingCurlyBracket") << code5 << 0 << 0 << true << Curly << Closing << 0 << 0 << true;

    // №6. Закрывающая квадратная скобка
    /*!
     * \test Тест 6: Закрывающая квадратная скобка
     * Проверяет корректное создание объекта для ']'
     */
    QStringList code6 = {"]"};
    QTest::newRow("closingSquareBracket") << code6 << 0 << 0 << true << Square << Closing << 0 << 0 << true;

    // №7. неправильные порядок
    /*!
     * \test Тест 7: Проверка выставления неправильного порядка
     * Проверяет обработку флага неправильного порядка
     */
    QStringList code7 = {"("};
    QTest::newRow("IncorrectOrder") << code7 << 0 << 0 << false << Round << Opening << 0 << 0 << false;

    // №8. правильные порядок
    /*!
     * \test Тест 8: Проверка выставления правильного порядка
     * Проверяет обработку флага правильного порядка
     */
    QStringList code8 = {"("};
    QTest::newRow("CorrectOrder") << code8 << 0 << 0 << true << Round << Opening << 0 << 0 << true;

    // №9. скобка не в начале кода
    /*!
     * \test Тест 9: Скобка не в начале кода
     * Проверяет корректное выставление позиции скобки не в начале строки
     */
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

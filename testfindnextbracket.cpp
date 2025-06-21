#include "testfindnextbracket.h"
#include <QStack>

testfindnextbracket::testfindnextbracket(QObject *parent) : QObject(parent) {}

void testfindnextbracket::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code"); ///< Исходный код для теста
    QTest::addColumn<int>("startLine"); ///< Стартовая строка поиска
    QTest::addColumn<int>("startPosition"); ///< Стартовая позиция в строке
    QTest::addColumn<errorininputdata>("error"); ///< Ошибки во входных данных
    QTest::addColumn<int>("bracketisfound"); ///< Флаг нахождения скобки
    QTest::addColumn<int>("exp_startLine"); ///< Ожидаемая строка скобки
    QTest::addColumn<int>("exp_startPosition"); ///< Ожидаемая позиция скобки
    QTest::addColumn<errorininputdata>("exp_error"); ///< Ожидаемая ошибка входных данных

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. нахождение скобки с начала кода
    /*!
     * \test Тест 1: Поиск с начала кода
     * Проверяет нахождение первой скобки в простом коде
     */
    QStringList test_code1 ={
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    errorininputdata error;
    errorininputdata newError;
    QTest::newRow("findBracketInBeginOfCode") << test_code1 << 0 << 0 << error << 1 << 0 << 8 << newError;

    //№2. пропуск однострочного комментария
    /*!
     * \test Тест 2: Пропуск однострочного комментария
     * Проверяет игнорирование скобок в однострочных комментариях
     */
    QStringList test_code2 = {
        "// comment (",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    QTest::newRow("skipOnelineCommentInCode") << test_code2 << 0 << 0 << error << 1 << 1 << 8 << newError;

    //№3. пропуск многострочного комментария (без ошибки)
    /*!
     * \test Тест 3: Пропуск многострочного комментария
     * Проверяет игнорирование скобок в многострочных комментариях
     */
    QStringList test_code3 = {
        "/* (comment ",
        "comment2] */",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    QTest::newRow("skipMultilineCommentInCode") << test_code3 << 0 << 0 << error << 1 << 2 << 8 << newError;

    //№4. пропуск многострочного комментария (с ошибкой)
    /*!
     * \test Тест 4: Незакрытый многострочный комментарий
     * Проверяет обработку ошибки незакрытого многострочного комментария
     */
    QStringList test_code4 = {
        "/* comment ",
        "int main()",
        "{",
        "int x = (5 + 3);",
        "}"
    };
    newError.setType(UnclosedMultilineComment);
    newError.setLine(0);
    newError.setPos(1);
    QTest::newRow("skipIncorrectMultilineCommentInCode") << test_code4 << 0 << 0 << error << -1 << 0 << 1 << newError;

    //№5. пропуск строковой константы (без ошибки)
    /*!
     * \test Тест 5: Пропуск строковой константы
     * Проверяет игнорирование скобок в строковых константах
     */
    QStringList test_code5 = {
        "int main()",
        "{",
        "QString a = \"Hello, [world]]!\";",
        "}"
    };
    newError.setType(NoError);
    newError.setLine(-1);
    newError.setPos(-1);
    QTest::newRow("skipStringConstantInCode") << test_code5 << 2 << 0 << error << 1 << 3 << 0 << newError;

    //№6. пропуск строковой константы (с ошибкой)
    /*!
     * \test Тест 6: Незакрытая строковая константа
     * Проверяет обработку ошибки незакрытой строковой константы
     */
    QStringList test_code6 = {
        "int main()",
        "{",
        "QString a = \"Hello, [world]]! ;",
        "}"
    };
    newError.setType(UnclosedStringConst);
    newError.setLine(2);
    newError.setPos(12);
    QTest::newRow("skipIncorrectStringConstantInCode") << test_code6 << 2 << 0 << error << -1 << 2 << 12 << newError;

    //№7. пропуск символьной коснтанты (без ошибки)
    /*!
     * \test Тест 7: Пропуск символьной константы
     * Проверяет игнорирование скобок в символьных константах
     */
    QStringList test_code7 = {
        "int main()",
        "{",
        "char a = \'(\';",
        "}"
    };
    newError.setType(NoError);
    newError.setLine(-1);
    newError.setPos(-1);
    QTest::newRow("skipCharConstantInCode") << test_code7 << 2 << 0 << error << 1 << 3 << 0 << newError;

    //№8. пропуск символьной константы (с ошибкой)
    /*!
     * \test Тест 8: Незакрытая символьная константа
     * Проверяет обработку ошибки незакрытого символьной константы
     */
    QStringList test_code8 = {
        "int main()",
        "{",
        "char a = \'( ;",
        "}"
    };
    newError.setType(UnclosedCharConst);
    newError.setLine(2);
    newError.setPos(9);
    QTest::newRow("skipIncorrectCharConstantInCode") << test_code8 << 2 << 0 << error << -1 << 2 << 9 << newError;

    //№9. комплексный тест - комбинация комментариев и констант
    /*!
     * \test Тест 9: Комплексный тест
     * Проверяет корректность работы в сложном коде с:
     * - Однострочными комментариями
     * - Многострочными комментариями
     * - Строковыми и символьными константами
     */
    QStringList test_code9 = {
        "int main()",
        "{",
        "// comment",
        "/* comment1",
        "comment2 */",
        "QString a = \"Hello, world!\";",
        "char b = \'H\';",
        "int x = (5+3);",
        "}"
    };
    newError.setType(NoError);
    newError.setLine(-1);
    newError.setPos(-1);
    QTest::newRow("complexTest") << test_code9 << 2 << 0 << error << 1 << 7 << 8 << newError;

    //№10. скобка не найдена
    /*!
     * \test Тест 10: Скобка не найдена
     * Проверяет обработку случая отсутствия скобок в коде
     */
    QStringList test_code10 = { "int x = 5 + 3;" };
    QTest::newRow("notFoundBracket") << test_code10 << 0 << 0 << error << 0 << 0 << 13 << newError;
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

#include "testskipstringconstant.h"

testskipstringconstant::testskipstringconstant(QObject *parent) : QObject(parent) {}

void testskipstringconstant::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code"); ///< Исходный код для теста
    QTest::addColumn<int>("currentLine"); ///< Текущая строка поиска
    QTest::addColumn<int>("currentPosition"); ///< Текущая позиция в строке
    QTest::addColumn<bool>("resultofskipping"); ///< Ожидаемый результат пропуска
    QTest::addColumn<int>("exp_currentLine"); ///< Ожидаемая строка после пропуска
    QTest::addColumn<int>("exp_currentPosition"); ///< Ожидаемая позиция после пропуска

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. простая строковая закрывающаяся константа
    /*!
     * \test Тест 1: Простая строковая константа
     * Проверяет корректный пропуск обычной строковой константы
     */
    QStringList test_code1 ={
        "int main()",
        "{",
        "QString a = \"Hello, world!\";",
        "}"
    };
    QTest::newRow("simpleClosingStringConst") << test_code1 << 2 << 12 << true << 2 << 26;

    //№2. экранированная кавычка
    /*!
     * \test Тест 2: Экранированная кавычка
     * Проверяет обработку экранированной кавычки \" внутри строковой константы
     */
    QStringList test_code2 ={
        "int main()",
        "{",
        "QString a = \"Hello, \\\"world!\";",
        "}"
    };
    QTest::newRow("escapedQuotationMarkInsideStringConst") << test_code2 << 2 << 12 << true << 2 << 28;

    //№3. экранированный слэш
    /*!
     * \test Тест 3: Экранированный слэш
     * Проверяет обработку экранированного слэша \\ внутри строковой константы
     */
    QStringList test_code3 ={
        "int main()",
        "{",
        "QString a = \"Hello, world!\\\\\";",
        "}"
    };
    QTest::newRow("escapedSlashInsideStringConst") << test_code3 << 2 << 12 << true << 2 << 28;

    //№4. незакрытая строковая константа
    /*!
     * \test Тест 4: Незакрытая строковая константа
     * Проверяет обработку незакрытой строковой константы
     */
    QStringList test_code4 = {
        "int main()",
        "{",
        "QString a = \"Hello, world! ;",
        "}"
    };
    QTest::newRow("unclosedStringConst") << test_code4 << 2 << 12 << false << 2 << 12;

    //№5. экранированная кавычка (ошибка)
    /*!
     * \test Тест 5: Неправильное экранирование кавычки
     * Проверяет обработку некорректно экранированной кавычки (т.е. незакрытая строковая константа)
     */
    QStringList test_code5 = {
        "int main()",
        "{",
        "QString a = \"Hello, world! \\\\\\\";",
        "}"
    };
    QTest::newRow("IncorrectEscapedQuotationMarkInsideStringConst") << test_code5 << 2 << 12 << false << 2 << 12;

    //№6. перенос строковой константы на другую строку
    /*!
     * \test Тест 6: Многострочная строковая константа
     * Проверяет обработку строковой константы с переносом
     */
    QStringList test_code6 ={
        "int main()",
        "{",
        "QString a = \"Hello, \\",
        "world!\";",
        "}"
    };
    QTest::newRow("multilineStringConst") << test_code6 << 2 << 12 << true << 3 << 6;

    //№7. пустая строковая константа
    /*!
     * \test Тест 7: Пустая строковая константа
     * Проверяет обработку пустой строковой константы
     */
    QStringList test_code7 = {
        "int main()",
        "{",
        "QString a = \"\";",
        "}"
    };
    QTest::newRow("emptyStringConst") << test_code7 << 2 << 12 << true << 2 << 13;

    //№8. перенос строковой константы без слэша (ошибка)
    /*!
     * \test Тест 8: Неправильный перенос строки
     * Проверяет обработку неправильного переноса строковой константы без экранирования
     */
    QStringList test_code8 = {
        "int main()",
        "{",
        "QString a = \"Hello, ",
        "world!\";",
        "}"
    };
    QTest::newRow("incorrectMultilineStringConst") << test_code8 << 2 << 12 << false << 2 << 12;
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

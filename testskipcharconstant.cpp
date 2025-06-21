#include "testskipcharconstant.h"

testskipcharconstant::testskipcharconstant(QObject *parent) : QObject(parent) {}

void testskipcharconstant::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code"); ///< Исходный код для теста
    QTest::addColumn<int>("currentLine"); ///< Текущая строка поиска
    QTest::addColumn<int>("currentPosition"); ///< Текущая позиция в строке
    QTest::addColumn<bool>("resultofskipping"); ///< Ожидаемый результат пропуска
    QTest::addColumn<int>("exp_currentLine"); ///< Ожидаемая строка после пропуска
    QTest::addColumn<int>("exp_currentPosition"); ///< Ожидаемая позиция после пропуска

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. простая символьная константа
    /*!
     * \test Тест 1: Простая символьная константа
     * Проверяет корректный пропуск обычной символьной константы
     */
    QStringList test_code1 ={
        "int main()",
        "{",
        "char a = \'H\';",
        "}"
    };
    QTest::newRow("simpleClosingCharConst") << test_code1 << 2 << 9 << true << 2 << 11;

    //№2. экранированная кавычка
    /*!
     * \test Тест 2: Экранированная кавычка
     * Проверяет обработку экранированной кавычки \' внутри константы
     */
    QStringList test_code2 ={
        "int main()",
        "{",
        "char a = \'\\\'\';",
        "}"
    };
    QTest::newRow("escapedQuotationMarkInsideCharConst") << test_code2 << 2 << 9 << true << 2 << 12;

    //№3. незакрытая константа
    /*!
     * \test Тест 3: Незакрытая константа
     * Проверяет обработку незакрытой символьной константы
     */
    QStringList test_code3 ={
        "int main()",
        "{",
        "char a = \'H;",
        "}"
    };
    QTest::newRow("unclosedCharConst") << test_code3 << 2 << 9 << false << 2 << 9;

    //№4. пустая константа
    /*!
     * \test Тест 4: Пустая константа
     * Проверяет обработку пустой символьной константы ''
     */
    QStringList test_code4 ={
        "int main()",
        "{",
        "char a = \'\';",
        "}"
    };
    QTest::newRow("emptyCharConst") << test_code4 << 2 << 9 << true << 2 << 10;

    //№5. экранированный слэш
    /*!
     * \test Тест 5: Экранированный слэш
     * Проверяет обработку экранированного слэша \\ внутри константы
     */
    QStringList test_code5 ={
        "int main()",
        "{",
        "char a = \'\\\\\';",
        "}"
    };
    QTest::newRow("escapedSlashInsideCharConst") << test_code5 << 2 << 9 << true << 2 << 12;

    //№6. неправильное экранирование слэша (ошибка)
    /*!
     * \test Тест 6: Неправильное экранирование
     * Проверяет обработку некорректно экранированного слэша (т.е. незакрытую константу)
     */
    QStringList test_code6 ={
        "int main()",
        "{",
        "char a = \'\\\';",
        "}"
    };
    QTest::newRow("incorrectEscapedSlashInsideCharConst") << test_code6 << 2 << 9 << false << 2 << 9;
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

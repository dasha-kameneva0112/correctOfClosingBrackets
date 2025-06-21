#include "testskipmultilinecomment.h"
#include <QStack>

testskipmultilinecomment::testskipmultilinecomment(QObject *parent) : QObject(parent) {}


void testskipmultilinecomment::add_data()
{
    // колонки параметры + ожидемый результат
    QTest::addColumn<QStringList>("code"); ///< Исходный код для теста
    QTest::addColumn<int>("currentLine"); ///< Текущая строка поиска
    QTest::addColumn<int>("currentPosition"); ///< Текущая позиция в строке
    QTest::addColumn<bool>("resultofskipping"); ///< Ожидаемый результат пропуска
    QTest::addColumn<int>("exp_currentLine"); ///< Ожидаемая строка после пропуска
    QTest::addColumn<int>("exp_currentPosition"); ///< Ожидаемая позиция после пропуска

    //Создаем строки‐тесты и заполняем таблицу данными
    //№1. корректный многострочный комментарий (на 2 строки)
    /*!
     * \test Тест 1: Корректный многострочный комментарий (2 строки)
     * Проверяет пропуск стандартного многострочного комментария, занимающего несколько строк
     */
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
    /*!
     * \test Тест 2: Комментарий в середине строки
     * Проверяет пропуск многострочного комментария, расположенного внутри строки кода (часть строки)
     */
    QStringList test_code2 = {
        "int main()",
        "{",
        "int /* comment */ x = 5;",
        "}"
    };
    QTest::newRow("correctMultilineCommentInPartOfLine") << test_code2 << 2 << 5 << true << 2 << 16;

    //№3. корректный многострочный комментарий (на одну строку)
    /*!
     * \test Тест 3: Однострочный многострочный комментарий
     * Проверяет обработку многострочного комментария, размещенного в одной строке
     */
    QStringList test_code3 ={
        "int main()",
        "{",
        "/* comment */",
        "int x = 5;",
        "}"
    };
    QTest::newRow("correctMultilineCommentInOneLine") << test_code3 << 2 << 1 << true << 2 << 12;

    //№4. незакрытый комментарий
    /*!
     * \test Тест 4:  Незакрытый комментарий
     * Проверяет обработку случая отсутствия закрывающего символа многострочного комментария
     */
    QStringList test_code4 = {
        "int main()",
        "{",
        "int x = 5;",
        "/* comment ",
        "}"
    };
    QTest::newRow("unclosedMultilineComment") << test_code4 << 3 << 1 << false << 3 << 1;

    //№5. пустой комментарий
    /*!
     * \test Тест 5: Пустой комментарий
     * Проверяет обработку пустого многострочного комментария
     */
    QStringList test_code5 = {
        "int main()",
        "{",
        "int x = 5;",
        "/**/",
        "}"
    };
    QTest::newRow("emptyMultilineComment") << test_code5 << 3 << 1 << true << 3 << 3;


    //№6. экранированный слэш и звездочка
    /*!
     * \test Тест 6: Экранированные символы
     * Проверяет обработку экранированных символов *\/ внутри многострочного комментария
     */
    QStringList test_code6 = {
        "int main()",
        "{",
        "int x = 5;",
        "/* *\\/ comment1 */",
        "}"
    };
    QTest::newRow("escapedSlashAndAsteriskSymbol") << test_code6 << 3 << 1 << true << 3 << 17;

    //№7. комплексный тест
    /*!
     * \test Тест 7: Комплексный тест
     * Проверяет обработку сложного многострочного комментария
     */
    QStringList test_code7 = {
        "int main()",
        "{",
        "int /* c*\\///om***me\\\\n*\\/t **/ x = 5;",
        "}"
    };
    QTest::newRow("complexTest") << test_code7 << 2 << 5 << true << 2 << 30;

    //№8. комментарий в конце кода (файла)
    /*!
     * \test Тест 8: Комментарий в конце файла
     * Проверяет обработку многострочного комментария, расположенного в конце кода
     */
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


#ifndef TESTSKIPSTRINGCONSTANT_H
#define TESTSKIPSTRINGCONSTANT_H
#include <QObject>
#include "main.h"

class testskipstringconstant : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testskipstringconstant(QObject *parent = nullptr);

private slots:
    void simpleClosingStringConst(); //№1. простая строковая закрывающаяся константа
    void escapedQuotationMarkInsideStringConst(); //№2. экранированная кавычка
    void escapedSlashInsideStringConst(); //№3. экранированный слэш
    void unclosedStringConst(); //№4. незакрытая строковая константа
    void IncorrectEscapedQuotationMarkInsideStringConst(); //№5. экранированная кавычка (ошибка)
    void multilineStringConst(); //№6. перенос строковой константы на другую строку
    void emptyStringConst(); //№7. пустая строковая константа
    void incorrectMultilineStringConst(); //№8. перенос строковой константы без слэша (ошибка)

};



#endif // TESTSKIPSTRINGCONSTANT_H

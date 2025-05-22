#ifndef TESTSKIPCHARCONSTANT_H
#define TESTSKIPCHARCONSTANT_H
#include <QObject>
#include "main.h"

class testskipcharconstant : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testskipcharconstant(QObject *parent = nullptr);
private slots:
    void simpleClosingCharConst(); //№1. простая символьная константа
    void escapedQuotationMarkInsideCharConst(); //№2. экранированная кавычка
    void unclosedCharConst(); //№3. незакрытая константа
    void emptyCharConst(); //№4. пустая константа
    void escapedSlashInsideCharConst(); //№5. экранированный слэш
    void incorrectEscapedSlashInsideCharConst(); //№6. неправильное экранирование слэша (ошибка)
};

#endif // TESTSKIPCHARCONSTANT_H

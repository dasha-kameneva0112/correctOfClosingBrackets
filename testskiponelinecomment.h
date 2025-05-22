#ifndef TESTSKIPONELINECOMMENT_H
#define TESTSKIPONELINECOMMENT_H
#include <QObject>
#include "main.h"

class testskiponelinecomment : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    testskiponelinecomment(QObject *parent = nullptr);
private slots:
    void standartOneLineComment(); //№1. стандартный однострочный комментарий (в конце строки)
    void onelineCommentInSeveralLine(); //№2. стандартный однострочный комментарий (в 2-3 строки)
    void escapedSlashInEndOfOnelineComment(); //№3. экранированный слэш в конце комментария
    void emptyOnelineComment(); //№4. пустой комментарий
    void onelineCommentInEndOfCode(); //№5. комментарий в конце кода

};

#endif // TESTSKIPONELINECOMMENT_H


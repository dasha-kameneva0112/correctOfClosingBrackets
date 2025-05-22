#ifndef TESTSKIPMULTILINECOMMENT_H
#define TESTSKIPMULTILINECOMMENT_H
#include <QObject>
#include "main.h"

class testskipmultilinecomment : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    testskipmultilinecomment(QObject *parent = nullptr);

private slots:
    void correctMultilineComment(); //№1. корректный многострочный комментарий (на 2 строки)
    void correctMultilineCommentInPartOfLine(); //№2. корректный многострочный комментарий (часть строки)
    void correctMultilineCommentInOneLine(); //№3. корректный многострочный комментарий (на одну строку)
    void unclosedMultilineComment(); //№4. незакрытый комментарий
    void emptyMultilineComment(); //№5. пустой комментарий
    void escapedSlashAndAsteriskSymbol(); //№6. экранированный слэш и звездочка
    void complexTest(); //№7. комплексный тест
    void multilineCommentInEndOfCode(); //№8. комментарий в конце кода (файла)
};

#endif // TESTSKIPMULTILINECOMMENT_H


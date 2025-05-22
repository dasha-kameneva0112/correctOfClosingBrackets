#ifndef TESTFINDNEXTBRACKET_H
#define TESTFINDNEXTBRACKET_H
#include <QObject>
#include "main.h"


class testfindnextbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindnextbracket(QObject *parent = nullptr);
private slots:
    void findBracketInBeginOfCode(); //№1. нахождение скобки с начала кода
    void skipOnelineCommentInCode(); //№2. пропуск однострочного комментария
    void skipIncorrectOnelineCommentInCode(); //№3. пропуск многострочного комментария (без ошибки)
    void skipMultilineCommentInCode(); //№4. пропуск многострочного комментария (с ошибкой)
    void skipIncorrectMultilineCommentInCode(); //№5. пропуск строковой константы (без ошибки)
    void skipStringConstantInCode(); //№6. пропуск строковой константы (с ошибкой)
    void skipIncorrectStringConstantInCode(); //№7. пропуск символьной коснтанты (без ошибки)
    void skipCharConstantInCode(); //№8. пропуск символьной константы (с ошибкой)
    void skipIncorrectCharConstantInCode(); //№9. комплексный тест - комбинация комментариев и констант
    void bracketIsNotFound(); //№10. скобка не найдена
};

#endif // TESTFINDNEXTBRACKET_H

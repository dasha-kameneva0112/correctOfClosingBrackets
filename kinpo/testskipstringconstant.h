#ifndef TESTSKIPSTRINGCONSTANT_H
#define TESTSKIPSTRINGCONSTANT_H
#include <QObject>
#include "main.h"


class testskipstringconstant : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    testskipstringconstant();
private slots:
    void simpleStringConst(); // №1. Простая строковая константа
    //void (); // №2. Экранированная кавычка (правильно) внутри константы
    //void (); // №3. Экранированный слэш (правильно)
    void unclosingConst(); // №4. Незакрытая строковая константа
    void incorrect(); // №5. Экранированная кавычка (неправильно)
    void MultilineConst(); // №6. Многострочная константа
    void emptyConst(); // №7. Пустая константа
    void incorrectTransfer(); // №8. Неправильный перенос на другую строку
};

#endif // TESTSKIPSTRINGCONSTANT_H

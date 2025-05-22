#ifndef TESTFINDALLINCORRECTUSESOFBRACKETS_H
#define TESTFINDALLINCORRECTUSESOFBRACKETS_H
#include <QObject>
#include "main.h"

class testfindallincorrectusesofbrackets : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindallincorrectusesofbrackets(QObject *parent = nullptr);
private slots:
    void findBracketInCorrectCode(); //№1. нахождение скобок в обычном корректном коде
    void codeWithSkippingConstantsAndCommentsWithBrackets(); //№2. код с комментариями и константами, содержащие скобки (комплексный тест1)
    void mistakeIsExcessiveClosingBracket(); //№3. ошибка - лишняя закрывающая скобка
    void mistakeIsUnclosedBracket(); //№4. ошибка - незакрытая скобка
    void mistakeIsIncorrectOrderOfBrackets(); //№5. ошибка - неправильный порядок
    void allMistakes(); //№6. комплексный тест2 - комбинация всех ошибок
    void severalSameMistakes(); //№7. комплексный тест3 - несколько одинаковых ошибок
    void errorIsUnclosedStringConst(); //№8. ошибка - незакрытая строковая константа
    void errorIsUnclosedCharConst(); //№9. ошибка - незакрытая символьная константа
    void errorIsUnclosedMultilineComment(); //№10. ошибка - незакрытый многострочный комментарий

};

#endif // TESTFINDALLINCORRECTUSESOFBRACKETS_H

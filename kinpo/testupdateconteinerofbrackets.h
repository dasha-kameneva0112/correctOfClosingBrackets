#ifndef TESTUPDATECONTEINEROFBRACKETS_H
#define TESTUPDATECONTEINEROFBRACKETS_H
#include <QObject>
#include "main.h"

class testupdateconteinerofbrackets : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testupdateconteinerofbrackets(QObject *parent = nullptr);
private slots:
    void addOpeningBracket(); // №1. Добавление открывающей скобки
    void addCorrectCLosingBracket(); // №2. Добавление закрывающей скобки (без ошибок)
    void addExcessiveClosingBracket(); // №3. Добавление закрывающей скобки (ошибка - нет пары, лишняя закрывающая)
    void addSeveralExcessiveBrackets(); // №4. В стеке есть несколько (3-4) скобок того же типа
    void incorrectOrderWithOneBracket(); // №5.1. Неправильный порядок с предыдущей
    void incorrectOrderWithAllBrackets(); // №5.2. Неправильный порядок с 3-4 всеми предыдущими
    void incorrectOrderWithSeveralBrackets(); // №5.3. Неправильный порядок с 3-4 предыдущими (не всеми)
    void addMistakeIncorrectOrder(); // №5.4. Добавление ошибки неправильного порядка (порядок уже изменен)
    void addMistakeInNotEmptyConteiner(); // №6. Добавление ошибки в непустой контейнер
    void complexTest(); // №7. Корректная вложенность
};

#endif // TESTUPDATECONTEINEROFBRACKETS_H




#ifndef TESTFINDCOUPLEFORBRACKET_H
#define TESTFINDCOUPLEFORBRACKET_H
#include <QObject>
#include "bracket.h"

extern int findCoupleForBracket(const bracket& newBracket, const QStack<bracket>& brackets);


class testfindcoupleforbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindcoupleforbracket(QObject *parent = nullptr);


private slots:
    void roundBracket(); // №1.1. Круглая скобка
    void squareBracket(); // №1.2. Квадратная скобка
    void curlyBracket(); // №1.3. Фигурная скобка
    void multipleBracketsOfTheSameType(); // №2. В стеке есть несколько (3-4) скобок того же типа
    void thereIsNoCouple(); // №3. В стеке нет пары
    void theStackIsEmpty(); // №4. Стек пустой
};

#endif // TESTFINDCOUPLEFORBRACKET_H

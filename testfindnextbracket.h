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
    void add_data(); //В этом слоте создается таблица данных
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTFINDNEXTBRACKET_H

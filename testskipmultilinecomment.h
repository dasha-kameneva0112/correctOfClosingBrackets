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
    void add_data(); //В этом слоте создается таблица данных
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTSKIPMULTILINECOMMENT_H


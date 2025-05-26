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
    void add_data(); //В этом слоте создается таблица данных
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTSKIPCHARCONSTANT_H

#ifndef TESTFINDCOUPLEFORBRACKET_H
#define TESTFINDCOUPLEFORBRACKET_H
#include <QObject>
#include "main.h"

class testfindcoupleforbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testfindcoupleforbracket(QObject *parent = nullptr);
private slots:
    void add_data(); //В этом слоте создается таблица данных
    void add(); //  слот за изъятие данных из таблицы и передачу их в тестируемый метод
};

#endif // TESTFINDCOUPLEFORBRACKET_H

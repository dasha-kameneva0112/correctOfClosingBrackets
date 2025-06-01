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
    void add_data();
    void add();
};

#endif // TESTFINDALLINCORRECTUSESOFBRACKETS_H

#ifndef TESTSKIPSTRINGCONSTANT_H
#define TESTSKIPSTRINGCONSTANT_H
#include <QObject>
#include "main.h"

class testskipstringconstant : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testskipstringconstant(QObject *parent = nullptr);

private slots:
    void add_data();
    void add();
};



#endif // TESTSKIPSTRINGCONSTANT_H

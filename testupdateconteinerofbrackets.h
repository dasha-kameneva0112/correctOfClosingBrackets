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
    void add_data();
    void add();
};

#endif // TESTUPDATECONTEINEROFBRACKETS_H




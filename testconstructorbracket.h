#ifndef TESTCONSTRUCTORBRACKET_H
#define TESTCONSTRUCTORBRACKET_H
#include <QObject>
#include "main.h"

class testconstructorbracket : public QObject
{
    Q_OBJECT //Обязательный макрос
public:
    explicit testconstructorbracket(QObject *parent = nullptr);
private slots:
    void add_data();
    void add();
};

#endif // TESTCONSTRUCTORBRACKET_H

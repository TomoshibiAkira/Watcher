#ifndef GRAPHIC_H
#define GARPHIC_H

#include "header.h"
#include <QSharedMemory>

class graphic : public QWidget
{
    Q_OBJECT

private:
    int ID;
    QSharedMemory sharedMemory;
    QLabel *status;

signals:
    void dataToGraphic(qreal);

public slots:
    void readData();

public:
    explicit graphic(int idNo, QWidget *parent = 0);
};

#endif // MAINWINDOW_H

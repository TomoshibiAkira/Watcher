#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QWidget>

#define EDGE 25
#define OFFSET 5

class graphicView : public QWidget
{
    Q_OBJECT

public:
    explicit graphicView(QWidget *parent);

public slots:
    void dataInput(qreal);

signals:
    void pointOver();

private:
    qreal zeroX, zeroY;
    QList<qreal> DataList, yList;
    int height, width, currentMonth, currentDay, currentMode;

protected:
    void paintEvent(QPaintEvent *);
};


#endif // GRAPHICVIEW_H

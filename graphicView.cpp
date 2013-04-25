#include "graphicView.h"
#include <QPainter>
#include <QPen>

graphicView::graphicView(QWidget *parent) :
    QWidget(parent)
{
    connect(this,SIGNAL(pointOver()),this,SLOT(update()));
    emit pointOver();
}

void graphicView::dataInput(qreal Data)
{
    if (DataList.count() == 60) DataList.clear();
    DataList.append(Data);
    emit pointOver();
}

void graphicView::dataClear()
{
    DataList.clear();
    emit pointOver();
}

void graphicView::paintEvent(QPaintEvent *)
{
        QPainter painter(this);

        QPen pen;
        QPen pen3;
        QPen pen5;

        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        pen.setBrush(Qt::red);
        pen.setCapStyle(Qt::RoundCap);

        pen3.setStyle(Qt::SolidLine);
        pen3.setWidth(2);
        pen3.setBrush(Qt::darkGray);

        pen5.setStyle(Qt::SolidLine);
        pen5.setWidth(2);
        pen5.setBrush(Qt::black);

        int height = this->size().height();
        int width = this->size().width();
        double padding = (height-EDGE*2) / 8;
        int number = 40;
        QString str;

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(Qt::darkGray);
        painter.setPen(pen3);
        painter.drawRect(EDGE+OFFSET,EDGE,width-EDGE*2,8*padding);
        painter.setBrush(Qt::black);

        painter.setPen(pen5);
        painter.drawLine(EDGE+OFFSET,EDGE,EDGE+OFFSET,EDGE+8*padding);
        painter.drawLine(EDGE+OFFSET,EDGE,width-EDGE+OFFSET,EDGE);
        painter.drawLine(width-EDGE+OFFSET,EDGE+8*padding,EDGE+OFFSET,EDGE+8*padding);
        painter.drawLine(width-EDGE+OFFSET,EDGE+8*padding,width-EDGE+OFFSET,EDGE);

        for (int i = 0;i < 8; i++)
        {
            painter.drawLine(EDGE+OFFSET,EDGE+(i+1)*padding,width-EDGE+OFFSET,EDGE+(i+1)*padding);
            str.setNum(number);
            painter.drawText(0,EDGE+i*padding-5,EDGE,10,Qt::AlignHCenter,str,0);
            number -= 10;
        }
        str = "-40";
        painter.drawText(0,EDGE+8*padding-5,EDGE,10,Qt::AlignHCenter,str,0);

        zeroX = EDGE+OFFSET;
        zeroY = EDGE+4 * padding;

        painter.translate(zeroX, zeroY);
        int dots = 60;

        yList.clear();
        for (int i = 0; i < dots; i++)
            yList.append(i * (width - EDGE * 2) / (dots-1));

        painter.setPen(pen);
        if (DataList.count() == 1)
        {
            painter.drawPoint(QPointF(yList.value(0),DataList.value(0) / 80 * (height-EDGE*2)));
        }
        else for (int i = 0; i < DataList.count()-1; i++)
        {
            painter.drawLine(yList.value(i),DataList.value(i) / 80 * (height-EDGE*2),
                         yList.value(i+1),DataList.value(i+1) / 80 * (height-EDGE*2));
        }
}

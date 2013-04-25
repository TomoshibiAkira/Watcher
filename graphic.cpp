#include "graphic.h"
#include "graphicView.h"

#include <QTimer>


graphic::graphic(int idNo, QWidget *parent) :
    QWidget(parent), sharedMemory("WatchServer")
{
    ID = idNo;
    graphicView *graph = new graphicView(this);
    QVBoxLayout *layout = new QVBoxLayout;
    status = new QLabel(this);
    status->setAlignment(Qt::AlignCenter);


    layout->addWidget(graph);
    status->resize(600, 30);
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    this->setLayout(layout);

    QTimer *timer = new QTimer(this);

    connect(this,SIGNAL(dataToGraphic(qreal)),
            graph,SLOT(dataInput(qreal)));
    connect(timer,SIGNAL(timeout()),this,SLOT(readData()));
    connect(this,SIGNAL(clearDataList()),graph,SLOT(dataClear()));
    timer->start(1000);

    this->resize(600,300);

}

void graphic::readData()
{
    // reading data from Shared Memory

    if (!sharedMemory.attach()) {
        status->setText(tr(("Unable to attach to shared memory segment. " \
                                   "Run WatchServer first.")));
        emit clearDataList();
        return;
    }

    status->clear();
    QBuffer buffer;
    QDataStream in(&buffer);
    QList<qreal> sensorValue;

    sharedMemory.lock();
    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> sensorValue;
    sharedMemory.unlock();

    sharedMemory.detach();

    if ((ID < 1) || (ID > sensorValue.count()-1))
    {
        status->setText(tr("This SENSOR ID is not VALID."));
        return;
    }

    emit dataToGraphic(sensorValue[ID]);
}

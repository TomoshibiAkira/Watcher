#ifndef ITEM_H
#define ITEM_H
#include "watcher.h"
#include <QGraphicsItem>
#include <QObject>

class Item : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Item(QPixmap pixmap, nodeData *dataRoot);

private:
    nodeData* root;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void updateSignal(nodeData*);
};

#endif // ITEM_H

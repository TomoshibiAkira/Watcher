#ifndef ITEM_H
#define ITEM_H
#include "watcher.h"
#include <QGraphicsItem>
#include <QObject>

//items showing on the GraphicView
class Item : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    //constructor, using pixmap
    Item(QPixmap pixmap, nodeData *dataRoot);

    //pixmap parameters
    int width, height;

private:
    //data address of current item in the tree
    nodeData* root;

protected:
    //reimplentation
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    //a signal to call updateWatcher, refresh the View
    void updateSignal(nodeData*);
};

#endif // ITEM_H

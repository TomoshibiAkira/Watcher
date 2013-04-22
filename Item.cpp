#include "Item.h"

Item::Item(QPixmap pixmap, nodeData* dataRoot)
{
    setPixmap(pixmap);
    root = dataRoot;

    width = pixmap.width();
    height = pixmap.height();
    setOffset(- height / 2, - width / 2);
    setPos(root->posX,root->posY);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateSignal(root);
}

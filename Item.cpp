#include "Item.h"

Item::Item(QPixmap pixmap, nodeData* dataRoot)
{
    setPixmap(pixmap);
    root = dataRoot;

    int width = pixmap.width();
    int height = pixmap.height();
    setOffset(-width / 2, -height / 2);
    setPos(root->posX,root->posY);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateSignal(root);
}

#include "Item.h"

Item::Item(QPixmap pixmap, nodeData* dataRoot)
{
    setPixmap(pixmap);
    root = dataRoot;

    width = pixmap.width();
    height = pixmap.height();
    //setting offset of the item
    setOffset(- height / 2, - width / 2);
    //setting position
    setPos(root->posX,root->posY);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateSignal(root);
}

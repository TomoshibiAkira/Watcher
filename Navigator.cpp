#include "Navigator.h"

/* Navigator class represents button on the navigation tool bar.
 * Inherits QAction class */

Navigator::Navigator(QString text, nodeData *root, QObject *parent)
    : QAction(parent) //constructor
{
    //icon creating
    QPixmap icon;
    icon = QPixmap(root->picPath);
    if (root->name.toUpper() == "FACTORY") icon = QPixmap("factory_back.png");
    icon = icon.scaled(QSize(22,22));

    //display setting
    setIcon(QIcon(icon));
    setIconText(text);
    this->root = root;

    //SINGAL | SLOT setting
    connect (this,SIGNAL(triggered()),this,SLOT(transfer()));
}

/* uses private slot transfer() to handle clicking event
 * emit updateSignal with a nodeData address parameter
 * to specify the level that user clicked */

void Navigator::transfer()
{
    emit updateSignal(root);
}

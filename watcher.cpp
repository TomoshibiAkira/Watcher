#include "watcher.h"
#include "Item.h"
Watcher::Watcher(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    rawValue = new QRadioButton("RAW",this);
    colorValue = new QRadioButton("Color",this);
    percentValue = new QRadioButton("Percent",this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(rawValue);
    buttonLayout->addStretch();
    buttonLayout->addWidget(colorValue);
    buttonLayout->addStretch();
    buttonLayout->addWidget(percentValue);
    buttonLayout->addStretch();

    View = new QGraphicsView(this);
    View->setScene(NULL);
    View->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    layout->addWidget(View);
    layout->addLayout(buttonLayout);

    QWidget* cWidget = new QWidget;
    cWidget->setLayout(layout);
    setCentralWidget(cWidget);
    resize(800,500);

    updateWatcher(Treeroot);

}

void Watcher::updateWatcher(nodeData* root)
{
    QGraphicsScene* scene = new QGraphicsScene;
    QString fileName = root->name.toLower();
    fileName.append("_back.png");
    View->setBackgroundBrush(QPixmap(fileName));

    QList<nodeData*> childs = root->child;
    for (int i = 0; i < childs.count(); i++)
    {
        Item *newChild = new Item(QPixmap(childs[i]->picPath), childs[i]);
        scene->addItem(newChild);
        connect(newChild,SIGNAL(updateSignal(nodeData*)),this,SLOT(updateWatcher(nodeData*)));
    }

    View->setScene(scene);
}

Watcher::~Watcher()
{
    
}

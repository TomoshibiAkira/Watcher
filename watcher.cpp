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
    backButton = new QPushButton("Back",this);

    buttonLayout->addWidget(rawValue);
    buttonLayout->addStretch();
    buttonLayout->addWidget(colorValue);
    buttonLayout->addStretch();
    buttonLayout->addWidget(percentValue);
    buttonLayout->addStretch();
    buttonLayout->addWidget(backButton);

    rawValue->setChecked(true);

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

    connect (rawValue,SIGNAL(clicked()),this,SLOT(updateStatus()));
    connect (colorValue,SIGNAL(clicked()),this,SLOT(updateStatus()));
    connect (percentValue,SIGNAL(clicked()),this,SLOT(updateStatus()));
    connect (backButton,SIGNAL(clicked()),this,SLOT(updateBack()));

}

void Watcher::updateBack()
{
    updateWatcher(currentRoot->parent);
}

void Watcher::updateStatus()
{
    updateWatcher(currentRoot);
}

void Watcher::updateWatcher(nodeData* root)
{
    currentRoot = root;
    if (currentRoot == Treeroot) backButton->setEnabled(false);
            else backButton->setEnabled(true);

    QGraphicsScene* scene;
    if (View->scene() != NULL)
    {
        scene = View->scene();
        View->setScene(NULL);
    }
    scene = new QGraphicsScene;
    QString fileName = root->name.toLower();
    fileName.append("_back.png");
    View->setBackgroundBrush(QPixmap(fileName));

    QList<nodeData*> childs = root->child;
    qreal posX, posY;
    for (int i = 0; i < childs.count(); i++)
    {
        Item *newChild = new Item(QPixmap(childs[i]->picPath), childs[i]);

        QGraphicsItem *statusAddress;
        if (rawValue->isChecked())
        {
            QGraphicsSimpleTextItem* status =
                    new QGraphicsSimpleTextItem(QString::number(childs[i]->value));
            QFont font = status->font();
            font.setPointSize(10);
            status->setFont(font);
            statusAddress = status;
            posX = newChild->height / 2 + childs[i]->posX;
            posY = newChild->width / 2 + childs[i]->posY;
        }
        else if (colorValue->isChecked())
        {
            QGraphicsEllipseItem* status = new QGraphicsEllipseItem;
            QBrush brush(Qt::green);
            status->setBrush(brush);
            status->setRect(-5, -5, 10, 10);
            statusAddress = status;
            posX = newChild->height / 2 + childs[i]->posX + 2;
            posY = newChild->width / 2 + childs[i]->posY + 2;
        }
        else if (percentValue->isChecked())
        {
            QGraphicsTextItem* status =
                    new QGraphicsTextItem("80%");
            QFont font = status->font();
            font.setPointSize(10);
            status->setFont(font);
            status->setDefaultTextColor(Qt::cyan);
            status->setEnabled(false);
            statusAddress = status;
            posX = newChild->height / 2 + childs[i]->posX - 3;
            posY = newChild->width / 2 + childs[i]->posY - 6;
        }
        statusAddress->setPos(posX, posY);

        scene->addItem(newChild);
        scene->addItem(statusAddress);
        if (childs[i]->name != "SENSOR")
            connect(newChild,SIGNAL(updateSignal(nodeData*)),this,SLOT(updateWatcher(nodeData*)));
    }

    View->setScene(scene);
}

Watcher::~Watcher()
{
    
}

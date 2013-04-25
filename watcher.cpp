#include "watcher.h"
#include "Item.h"
#include "graphic.h"
Watcher::Watcher(QWidget *parent)
    : QMainWindow(parent)
{
    //UI Settings
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

    //GraphicView setting
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

    //SIGNAL | SLOT setting
    connect (rawValue,SIGNAL(clicked()),this,SLOT(updateStatus()));
    connect (colorValue,SIGNAL(clicked()),this,SLOT(updateStatus()));
    connect (percentValue,SIGNAL(clicked()),this,SLOT(updateStatus()));
    connect (backButton,SIGNAL(clicked()),this,SLOT(updateBack()));

}

void Watcher::updateBack()
{
    //pressing back button
    updateWatcher(currentRoot->parent);
}

void Watcher::updateStatus()
{
    //changing status view mode
    updateWatcher(currentRoot);
}

void Watcher::updateWatcher(nodeData* root)
{
    //setting current root
    currentRoot = root;
    //back button enable (or not) setting
    if (currentRoot == Treeroot) backButton->setEnabled(false);
            else backButton->setEnabled(true);

    //setting new scene
    QGraphicsScene* scene = new QGraphicsScene;

    //setting background picture
    QString fileName = root->name.toLower();
    fileName.append("_back.png");
    View->setBackgroundBrush(QPixmap(fileName));

    //setting item and status
    QList<nodeData*> childs = root->child;
    qreal posX, posY;
    for (int i = 0; i < childs.count(); i++)
    {
        //setting item
        Item *newChild = new Item(QPixmap(childs[i]->picPath), childs[i]);

        //setting status
        QGraphicsItem *statusAddress;
        if (rawValue->isChecked())
        {
            //RAW mode, which means showing value from XML directly
            QGraphicsSimpleTextItem* status =
                    new QGraphicsSimpleTextItem(QString::number(childs[i]->value));
            QFont font = status->font();
            font.setPointSize(10);
            status->setFont(font);
            statusAddress = status;

            //minor position changing
            posX = newChild->height / 2 + childs[i]->posX;
            posY = newChild->width / 2 + childs[i]->posY;
        }
        else if (colorValue->isChecked())
        {
            //Color mode, uses green circle to represent working status
            //Fixed on green for now
            QGraphicsEllipseItem* status = new QGraphicsEllipseItem;
            QBrush brush(Qt::green);
            status->setBrush(brush);
            status->setRect(-5, -5, 10, 10);
            statusAddress = status;

            //minor position changing
            posX = newChild->height / 2 + childs[i]->posX + 2;
            posY = newChild->width / 2 + childs[i]->posY + 2;
        }
        else if (percentValue->isChecked())
        {
            //Percent mode, uses percent value to represent working status
            //Fixed on 80% for now
            QGraphicsTextItem* status =
                    new QGraphicsTextItem("80%");
            QFont font = status->font();
            font.setPointSize(10);
            status->setFont(font);
            status->setDefaultTextColor(Qt::cyan);
            status->setEnabled(false);
            statusAddress = status;

            //minor position changing
            posX = newChild->height / 2 + childs[i]->posX - 3;
            posY = newChild->width / 2 + childs[i]->posY - 6;
        }
        statusAddress->setPos(posX, posY);

        scene->addItem(newChild);
        scene->addItem(statusAddress);

        //event handler setting
        if (childs[i]->name != "SENSOR")
            connect(newChild,SIGNAL(updateSignal(nodeData*)),this,SLOT(updateWatcher(nodeData*)));
        else
            connect(newChild,SIGNAL(updateSignal(nodeData*)),this,SLOT(realtimeStart(nodeData*)));
    }

    //init scene
    View->setScene(scene);
}

void Watcher::realtimeStart(nodeData* root)
{
    graphic *graph = new graphic(root->ID, NULL);
    graph->show();
}

Watcher::~Watcher()
{
    
}

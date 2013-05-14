#include "watcher.h"
#include "Item.h"
#include "graphic.h"
#include "Navigator.h"
Watcher::Watcher(QWidget *parent)
    : QMainWindow(parent)
{
    //UI Settings

    //"Option" Menu
    showOption = new QMenu("&Option");
    colorValue = new QAction("By &Color",this);
    colorValue->setCheckable(true);
    percentValue = new QAction("By &Percent",this);
    percentValue->setCheckable(true);
    rawValue = new QAction("&RAW Value",this);
    rawValue->setCheckable(true);

    QActionGroup* showActions = new QActionGroup(this);
    showActions->addAction(colorValue);
    showActions->addAction(percentValue);
    showActions->addAction(rawValue);
    rawValue->setChecked(true);
    showOption->addActions(showActions->actions());

    //"About" Menu
    about = new QMenu("&About");
    aboutQt = new QAction("About &Qt...",this);
    QAction* EXIT = new QAction("&Exit",this);
    about->addAction(aboutQt);

    //"Exit" Button, add to main menu
    this->menuBar()->addMenu(showOption);
    this->menuBar()->addMenu(about);
    this->menuBar()->addAction(EXIT);

    //create navigation bar
    toolBar = new QToolBar;
    this->addToolBar(toolBar);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QVBoxLayout* layout = new QVBoxLayout;

    //GraphicView setting
    View = new QGraphicsView;
    View->setScene(NULL);
    View->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    layout->addWidget(View);

    QWidget* cWidget = new QWidget;
    cWidget->setLayout(layout);
    setCentralWidget(cWidget);
    resize(800,500);

    updateWatcher(Treeroot);

    //SIGNAL | SLOT setting
    connect (rawValue,SIGNAL(triggered()),this,SLOT(updateStatus()));
    connect (colorValue,SIGNAL(triggered()),this,SLOT(updateStatus()));
    connect (percentValue,SIGNAL(triggered()),this,SLOT(updateStatus()));
    connect (aboutQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect (EXIT,SIGNAL(triggered()),this,SLOT(close()));

}

void Watcher::updateStatus()
{
    //changing status view mode
    updateWatcher(currentRoot);
}

void Watcher::updateToolBar(nodeData* root)
{
    // search for current node, if there's no such node, add it into stackList
    int i = stackList.indexOf(root);
    if (i != -1)
        while (stackList.size() != i+1) stackList.removeLast();
    else
        stackList.append(root);

    // reset navigation bar
    toolBar->clear();
    // reset window title
    QString title = "Watch System - FACTORY", nodetitle = "FACTORY";

    /* nodetitle represents the text of this button
     * stackList[0] represents the node address this button corresponds
     * third parameter for QAction constructor, usually "this" */

    // create FACTORY button
    Navigator* node = new Navigator(nodetitle, stackList[0], this);
    toolBar->addAction(node);
    connect (node,SIGNAL(updateSignal(nodeData*)),this,SLOT(updateWatcher(nodeData*)));

    // create other buttons
    for (i = 1; i < stackList.size(); i++)
    {
        nodetitle = QString("%1 %2").arg(stackList[i]->name).arg(stackList[i]->ID);
        title += " > " + nodetitle;
        Navigator* node = new Navigator(nodetitle,stackList[i],this);
        toolBar->addAction(node);
        connect (node,SIGNAL(updateSignal(nodeData*)),this,SLOT(updateWatcher(nodeData*)));
    }

    // setting window title
    this->setWindowTitle(title);
}

void Watcher::updateWatcher(nodeData* root)
{
    //update the navigation bar and window title
    updateToolBar(root);

    //setting current root
    currentRoot = root;

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
    //open the graphic window to start capturing real time data
    graphic *graph = new graphic(root->ID, NULL);
    graph->show();
}

Watcher::~Watcher()
{
    
}

#ifndef WATCHER_H
#define WATCHER_H
#include "header.h"
#include <QMainWindow>

//Main class
class Watcher : public QMainWindow
{
    Q_OBJECT
    
public:
    Watcher(QWidget *parent = 0);
    ~Watcher();

private:
    QMenuBar *mainMenu;
    QToolBar *toolBar;
    QMenu* showOption,*about;
    QGraphicsView* View;
    QAction* rawValue, *colorValue, *percentValue;
    QAction* aboutQt;
    nodeData* currentRoot;
    QList<nodeData*> stackList;     //saves nodes that user had clicked

private:
    //uses for updating navigation bar and the window title
    void updateToolBar(nodeData* root);

public slots:
    //uses for updating the scene
    void updateWatcher(nodeData* root);
    //uses for updating Status mode, calls updateWatcher
    void updateStatus();
    //uses for opening realtime watcher
    void realtimeStart(nodeData*);
};

//EXTERN VARIABLE Treeroot saves the address of dta tree root
extern nodeData* Treeroot;

#endif // WATCHER_H

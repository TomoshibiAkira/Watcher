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
    QGraphicsView* View;
    QRadioButton* rawValue;
    QRadioButton* colorValue;
    QRadioButton* percentValue;
    QPushButton* backButton;
    nodeData* currentRoot;

public slots:
    //uses for updating the scene
    void updateWatcher(nodeData* root);
    //uses for updating Status mode, calls updateWatcher
    void updateStatus();
    //uses for back button, calls updateWatcher
    void updateBack();
    //uses for opening realtime watcher
    void realtimeStart(nodeData*);
};

//EXTERN VARIABLE Treeroot saves the address of dta tree root
extern nodeData* Treeroot;

#endif // WATCHER_H

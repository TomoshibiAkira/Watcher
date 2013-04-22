#ifndef WATCHER_H
#define WATCHER_H
#include "header.h"
#include <QMainWindow>

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
    void updateWatcher(nodeData* root);
    void updateStatus();
    void updateBack();
};

extern nodeData* Treeroot;

#endif // WATCHER_H

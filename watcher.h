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

public slots:
    void updateWatcher(nodeData* root);
};

extern nodeData* Treeroot;

#endif // WATCHER_H

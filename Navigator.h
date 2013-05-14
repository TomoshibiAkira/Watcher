#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QAction>
#include "watcher.h"

class Navigator : public QAction
{
    Q_OBJECT

public:
    Navigator(QString text, nodeData* root, QObject* parent);

private:
    nodeData* root;

signals:
    void updateSignal(nodeData*);

private slots:
    void transfer();
};

#endif // NAVIGATOR_H

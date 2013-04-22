#ifndef HEADER_H
#define HEADER_H

#include <QtGui>
#include <QWidget>
#include <QtXmlPatterns>
#include <QDomDocument>

class nodeData
{
public:
    //data recieved from XML
    int posX,posY,ID,value;
    QString picPath,name;

    //child nodes
    QList<nodeData*> child;

    //parent node
    nodeData* parent;
};




#endif // HEADER_H

#ifndef HEADER_H
#define HEADER_H

#include <QtGui>
#include <QWidget>
#include <QtXmlPatterns>
#include <QDomDocument>

class nodeData
{
public:
    int posX,posY,ID,value;
    QString picPath,name;
    QList<nodeData*> child;
};




#endif // HEADER_H

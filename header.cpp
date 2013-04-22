#include "header.h"

nodeData* Treeroot;
QFile file, fileXML;
QDomDocument doc;

bool readFile(QString fileName)
{
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(NULL, QWidget::tr("XSDRead"),
                         QWidget::tr("Cannot read file %1:\n%2.")
                         .arg(fileName)
                         .arg(file.errorString()));
        return false;
    }
    return true;
}

void parseElement(nodeData* root,const QDomElement &element)
{
    nodeData* temp = NULL;
    root->name = element.tagName();
    root->ID = element.attribute("id").toInt();
    root->picPath = element.attribute("pic");
    QDomElement x = element.firstChildElement().firstChildElement();
    QDomElement y = x.nextSiblingElement();
    root->posX = x.text().toInt();
    root->posY = y.text().toInt();
    QDomElement child = element.firstChildElement().nextSiblingElement();
    if (child.tagName() == "VALUE")
    {
        root->value = child.text().toInt();
    }
    else
    {
        while (!child.isNull())
        {
            temp = new nodeData;
            root->child.append(temp);
            parseElement(temp,child);
            temp->parent = root;
            child = child.nextSiblingElement();
        }
        int sum = 0;
        for (int i = 0; i < root->child.count(); i++)
            sum += root->child[i]->value;
        root->value =(int) (sum / root->child.count());
    }
}

void filePick()
{
    //Read XSD
    QString fileName =
            QFileDialog::getOpenFileName(NULL, QWidget::tr("Open XSD Files"),
                                         QDir::currentPath(),
                                         QWidget::tr("XSD Files (*.xsd)"));
    if (fileName.isEmpty()) return;
    file.setFileName(fileName);
    if (!readFile(fileName)) return;

    QXmlSchema schema;
    schema.load(&file);
    if (!schema.isValid())
    {
        QMessageBox::information(NULL, QWidget::tr("XSDRead")
                                 ,QWidget::tr("This is not a valid XSD File!"));
    }

    file.close();

    //Read XML
    fileName =
            QFileDialog::getOpenFileName(NULL, QWidget::tr("Open XML Files"),
                                         QDir::currentPath(),
                                         QWidget::tr("XML Files (*.xml)"));
    if (fileName.isEmpty()) return;
    file.setFileName(fileName);
    if (!readFile(fileName)) return;

    //DOM Read-In
    QString errorStr;
    int errorLine, errorColumn;
    if (!doc.setContent(&file, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::information(NULL, QWidget::tr("XSDRead"),
                                 QWidget::tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return;
    }

    //Reset the file pointer
    file.reset();

    //XSD Validator
    QXmlSchemaValidator validator(schema);
    if (!validator.validate(&file))
    {
        QMessageBox::information(NULL,QWidget::tr("XSDRead"),
                                 QWidget::tr("This is not a valid XML File!"));
        return;
    }

    // Building the tree
    QDomElement node = doc.documentElement();
    nodeData* temp = NULL;
    Treeroot = new nodeData;
    Treeroot->name = node.tagName();
    QDomElement child = node.firstChildElement();
    while (!child.isNull())
    {
        temp = new nodeData;
        Treeroot->child.append(temp);
        parseElement(temp,child);
        temp->parent = Treeroot;
        child = child.nextSiblingElement();
    }
}

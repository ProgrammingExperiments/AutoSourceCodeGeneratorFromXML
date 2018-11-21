#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "jlrxmlparser.h"


JlrXmlParser::JlrXmlParser(void)
{
    qDebug()<<"XML Parser construtor called";
}

bool JlrXmlParser::read(QIODevice *device)
{
    jlrXml.setDevice(device);

    if (jlrXml.readNextStartElement())
    {
        if (jlrXml.name() == QLatin1String("Root"))
        {
            readXML();
        }
        else
        {
            jlrXml.raiseError(QObject::tr("The file is not an XML version 1.0 file."));
        }
    }

    return !jlrXml.error();
}

void JlrXmlParser::readXML()
{
    Q_ASSERT(jlrXml.isStartElement() && jlrXml.name() == QLatin1String("Root"));
    qDebug()<<"Read XML called";

    while (jlrXml.readNextStartElement())
    {
        if (jlrXml.name() == QLatin1String("folder"))
        {
            //readFolder(0);
        }
        else if (jlrXml.name() == QLatin1String("bookmark"))
        {
           //readBookmark(0);
        }
        else if (jlrXml.name() == QLatin1String("separator"))
        {
            //readSeparator(0);
        }
        else
        {
           //jlrXml.skipCurrentElement();
        }
    }
}

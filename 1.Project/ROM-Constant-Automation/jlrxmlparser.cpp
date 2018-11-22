#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "jlrxmlparser.h"
#include "xmldatatype.h"
#include "mainwindow.h"


JlrXmlParser::JlrXmlParser(QStatusBar* status)
              :statusBar(status)
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


    while(!jlrXml.atEnd() && !jlrXml.hasError())
    {
        jlrXml.readNext();
        if(jlrXml.isStartElement())
        {
            if(jlrXml.name() == "Information")
            {
                qDebug()<<"Information";
                processXmlInformation();
            }
            else if(jlrXml.name() == "VIP_ConstantEnums")
            {
                qDebug()<<"VIP_ConstantEnums";
            }
            else if(jlrXml.name() == "VIP_ConstantValues")
            {
                qDebug()<<"VIP_ConstantValues";
            }
            else if(jlrXml.name() == "GIP_ConstantValues")
            {
                qDebug()<<"GIP_ConstantValues";
            }
            else if(jlrXml.name() == "VIP_ConstantTables")
            {
                qDebug()<<"VIP_ConstantTables";
            }
            else if(jlrXml.name() == "VIP_ConstantMaps")
            {
                qDebug()<<"VIP_ConstantMaps";
            }
            else
            {

            }
        }
    }
}


void JlrXmlParser::processXmlInformation(void)
{
    Q_ASSERT(jlrXml.isStartElement() && jlrXml.name() == QLatin1String("Information"));

    while (jlrXml.readNextStartElement())
    {
        if (jlrXml.name() == QLatin1String("Variants"))
        {
            QString variantData = jlrXml.readElementText();
            UpdateVariantInfo(variantData);
        }
        else if(jlrXml.name() == QLatin1String("Revision"))
        {
            qDebug()<<"Revision String - "<<jlrXml.readElementText();
        }
        else
        {
            jlrXml.skipCurrentElement();
        }
    }
}

void JlrXmlParser::UpdateVariantInfo(const QString &variantData)
{
    uint8_t index = 0;
    QRegExp splitToken(",");
    variantList = variantData.split(splitToken);
    qDebug()<<"Orgnl variant string - "<<variantData;
    qDebug()<<"variant string length - "<<variantList.length();

    /* Update the variant selection combo box with parsed data */
    while(index<variantList.length())
    {
        QString element = variantList.value(index);
        window->UpdateSelectVariantComboBox(element);
        //qDebug()<<index<<" - "<<element.trimmed();
        index++;
    }
}

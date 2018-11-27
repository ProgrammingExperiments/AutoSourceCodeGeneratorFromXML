#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QStringList>

#include "jlrxmlparser.h"
#include "mainwindow.h"
#include "errorcodes.h"


JlrXmlParser::JlrXmlParser()
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
                processXmlInformation();
            }
            else if(jlrXml.name() == "VIP_ConstantEnums")
            {
                qDebug()<<"********VIP_ConstantEnums********";
                processVipConstantEnums();
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
            UpdateVariantInfo(jlrXml.readElementText());
        }
        else if(jlrXml.name() == QLatin1String("Revision"))
        {
            UpdateXmlVersion(jlrXml.readElementText());
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
    romDataInfo.variantList = variantData.split(splitToken);
    romDataInfo.variantList.replaceInStrings(QRegExp("^\\s+|\\s+$"), "");

    qDebug()<<"Total No.of variants -> "<<romDataInfo.variantList.length();

    /* Update the variant selection combo box with parsed data */
    while(index<romDataInfo.variantList.length())
    {
        qDebug()<<"Variant "<<(index+1)<<" - "<<romDataInfo.variantList.value(index);
        index++;
    }
}

void JlrXmlParser::UpdateXmlVersion(const QString &xmlVersion)
{
    romDataInfo.version = xmlVersion;
    qDebug()<<"Version from fn "<<romDataInfo.version;
}

void JlrXmlParser::processVipConstantEnums(void)
{
    Q_ASSERT(jlrXml.isStartElement() && jlrXml.name() == QLatin1String("VIP_ConstantEnums"));

    while(!(jlrXml.tokenType() == QXmlStreamReader::EndElement &&
            jlrXml.name() == "VIP_ConstantEnums"))
    {
        if(jlrXml.tokenType() == QXmlStreamReader::StartElement)
        {
            /* Ensure, start element is the VIP const enum name */
            if(jlrXml.name().startsWith("CONST_ENUM_"))
            {
                updateVipConstEnumTable(jlrXml);
            }
        }
        jlrXml.readNext();
    }

}

ERROR_CODES_T JlrXmlParser::updateVipConstEnumTable(QXmlStreamReader &xml)
{
    ERROR_CODES_T errorCode = ERR_OK;
    const QString constEnumName = xml.name().toString();
    ROM_DATA_VIP_CONST_ENUMS vipConstEnum;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == constEnumName))
        {
            if(jlrXml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name().toString() == constEnumName)
                {
                    vipConstEnum.name = xml.name().toString();
                    qDebug()<<vipConstEnum.name;
                }
                else if(xml.name() == "Group")
                {
                    vipConstEnum.group = xml.readElementText();
                }
                else if(xml.name() == "Domain")
                {

                }
                else if(xml.name() == "Value")
                {

                }
                else
                {

                }
            }
            xml.readNext();
        }
        romDataConstVipEnum.append(vipConstEnum);
    }

    return errorCode;
}

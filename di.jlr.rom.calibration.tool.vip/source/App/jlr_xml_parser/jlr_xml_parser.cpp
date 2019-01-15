/*****************************************************************************
**                                                                            *
**              CONFIDENTIAL VISTEON CORPORATION                              *
**                                                                            *
** This is an unpublished work of authorship, which contains trade            *
** secrets, created in 2018. Visteon Corporation owns all rights to           *
** this work and intends to maintain it in confidence to preserve             *
** its trade secret status. Visteon Corporation reserves the right,           *
** under the copyright laws of the United States or those of any              *
** other country that may have jurisdiction, to protect this work             *
** as an unpublished work, in the event of an inadvertent or                  *
** deliberate unauthorized publication. Visteon Corporation also              *
** reserves its rights under all copyright laws to protect this               *
** work as a published work, when appropriate. Those having access            *
** to this work may not copy it, use it, modify it or disclose the            *
** information contained in it without the written authorization              *
** of Visteon Corporation.                                                    *
**                                                                            *
*******************************************************************************/
/**============================================================================
**
** Component Name   : di.jlr.rom.calibration.tool.vip
**
** File Name        : jlr_xml_parser.cpp
**
** Author           : Anil Joseph
**
** Description      : Class implementation for JLR XML Parser
**
** Organization     : Driver Information Software Section,
**                    DI Core Engineering Department
**
**============================================================================*/

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "jlr_xml_parser/jlr_xml_parser.h"
#include "main_window/main_window.h"
#include "error_handler/error_codes.h"
#include <iostream>

/******************************************************************************
 *                              Static Variable Declarations                  *
 ******************************************************************************/
static ROM_CONST_PARSED_STATUS romDataParsedStatus[MAX_ROM_CONST_TYPES];

using namespace std;
/*******************************************************************************
 Function Name     : JlrXmlParser::JlrXmlParser

 Description       : Constructor for class JlrXmlParser

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
JlrXmlParser::JlrXmlParser()
{
    resetRomConstParsedStatus();
}

/*******************************************************************************
 Function Name     : JlrXmlParser::read

 Description       : Reads the XML file and verify whether the XML file
                     contains a root element or not. If the XML file, doesn't
                     contain a root element, parsing error will be raised.

 Parameters        : QIODevice Object

 Return Value      : Returns FALSE, if the root element is not present.

 Critical Section  : None
 *******************************************************************************/
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

/*******************************************************************************
 Function Name     : JlrXmlParser::readXML

 Description       : Reads the XML file and verify whether the XML file
                     contains the tags for all ROM constant data types.
                     If the XML tag for a particular ROM data type is found,
                     corresponding parsing functions will be called to extract
                     the ROM constant values from JLR XML file.

 Parameters        : None

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::readXML()
{
    Q_ASSERT(jlrXml.isStartElement() && jlrXml.name() == QLatin1String("Root"));
    ERROR_CODES_T errorCode = ERR_OK;

    while(!jlrXml.atEnd() && !jlrXml.hasError())
    {
        jlrXml.readNext();
        if(jlrXml.isStartElement())
        {
            if(jlrXml.name() == "Information")
            {
                processXmlInformation(jlrXml);
            }
            else if(jlrXml.name() == "VIP_ConstantEnums")
            {
                errorCode = processVipConstantEnumTag(jlrXml);
            }
            else if(jlrXml.name() == "VIP_ConstantValues")
            {
                qDebug()<<"<VIP_ConstantValues>";
                errorCode = processVipConstantValueTag(jlrXml);

                /* Debug Print VIP CONST VALUE QList contents */
                //printQListVipConstValueContents(romDataConstVipValuesList);
            }
            else if(jlrXml.name() == "GIP_ConstantValues")
            {
                qDebug()<<"<GIP_ConstantValues>";
                errorCode = processGipConstantValueTag(jlrXml);

                /* Debug Print GIP CONST VALUE QList contents */
                //printQListGipConstValueContents(romDataConstGipValuesList);
            }
            else if(jlrXml.name() == "VIP_ConstantTables")
            {
                /*
                 * Member functions for parsing VIP CONST TABLES
                 * needs to be added here.
                 */
                qDebug()<<"<VIP_ConstantTables>";
                errorCode = processVipConstantTablesTag(jlrXml);
            }
            else if(jlrXml.name() == "VIP_ConstantMaps")
            {
                /*
                 * Member functions for parsing GIP CONST MAPS
                 * needs to be added here.
                 */
                qDebug()<<"<VIP_ConstantMaps>";
            }
            else
            {

            }
        }
    }

    if(jlrXml.hasError())
    {
        errorCode = ERR_UNABLE_TO_READ_JLR_XML;
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::processXmlInformation

 Description       : Reads the XML file and updates the information about
                     xml version and variant names.

 Parameters        : QXmlStreamReader Object

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void JlrXmlParser::processXmlInformation(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Information"));

    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("Variants"))
        {
            UpdateVariantInfo(xml.readElementText());
        }
        else if(xml.name() == QLatin1String("Revision"))
        {
            UpdateXmlVersion(xml.readElementText());
        }
        else
        {
            xml.skipCurrentElement();
        }
    }
}

/*******************************************************************************
 Function Name     : JlrXmlParser::UpdateVariantInfo

 Description       : Updates the variant info into the internal data structure.

 Parameters        : QString object

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void JlrXmlParser::UpdateVariantInfo(const QString &variantData)
{
    QRegExp splitToken(",");
    romDataInfo.variantList = variantData.split(splitToken);
    romDataInfo.variantList.replaceInStrings(QRegExp("^\\s+|\\s+$"), "");
}

/*******************************************************************************
 Function Name     : JlrXmlParser::UpdateXmlVersion

 Description       : Updates the xml version into the internal data structure.

 Parameters        : QString object

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void JlrXmlParser::UpdateXmlVersion(const QString &xmlVersion)
{
    romDataInfo.version = xmlVersion;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::processVipConstantEnums

 Description       : Initiates the processing for all of the
                     VIP CONST ENUM constants and updates the parsing status.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::processVipConstantEnumTag(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("VIP_ConstantEnums"));
    ERROR_CODES_T errorCode = ERR_OK;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "VIP_ConstantEnums") && !(xml.hasError()))

    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            /* Ensure, start element is the VIP const enum name */
            if(xml.name().startsWith("CONST_"))
            {
                parseVipConstEnumElements(xml);
            }
        }
        xml.readNext();
    }

    if(xml.hasError())
    {
        errorCode = ERR_VIP_CONST_ENUM_XML_PARSING_FAILED;
    }
    else
    {
        /* Successfully parsed and loaded the VIP CONST ENUM contents
         * to the internal data structure.
         * Update parsed status for VIP CONST ENUMS.
         */
        setRomConstParsedStatus(ROM_TYPE_VIP_CONST_ENUMS);
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumTable

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     all of the sub fields in VIP ENUM constants into internal
                     data structure.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::parseVipConstEnumElements(QXmlStreamReader &xml)
{
    ERROR_CODES_T errorCode = ERR_OK;
    const QString constEnumName = xml.name().toString();
    ROM_DATA_VIP_CONST_ENUMS vipConstEnum;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_ENUM_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == constEnumName) && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name().toString() == constEnumName)
                {
                    vipConstEnum.name = xml.name().toString();
                }
                else if(xml.name() == "Group")
                {
                    vipConstEnum.group = xml.readElementText();
                }
                else if(xml.name() == "Domain")
                {
                    /* Skip 'Domain' tag as we're not interested in the domain data now.
                     * The next version of tool can perform some additional error
                     * checking on the constant values with the value given in the
                     * 'Domain' tag.
                     */
                }
                else if(xml.name() == "Value")
                {
                    updateVipConstEnumVariantValues(jlrXml,&vipConstEnum);
                }
                else
                {

                }
            }
            xml.readNext();
        }
        romDataConstVipEnumList.append(vipConstEnum);
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::updateVipConstEnumVariantValues(QXmlStreamReader &xml,\
                                                            ROM_DATA_VIP_CONST_ENUMS*\
                                                            vipConstEnum)
{
    ERROR_CODES_T errorCode = ERR_OK;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_ENUM_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == "Value") && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() != "Value")
                {
                    vipConstEnum->variant.insert(xml.name().toString(),xml.readElementText());
                }
            }
            xml.readNext();
        }
    }

    return errorCode;
}


/*******************************************************************************
 Function Name     : resetRomConstParsedStatus

 Description       : Clears the ROM CONST parsed status.

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void resetRomConstParsedStatus(void)
{
    uint8_t index = 0;
    romDataParsedStatus[0].romConstType   = ROM_TYPE_VIP_CONST_ENUMS;
    romDataParsedStatus[0].variantCfgFile = "vipConstEum.cfg";

    romDataParsedStatus[1].romConstType = ROM_TYPE_VIP_CONST_VALUES;
    romDataParsedStatus[1].variantCfgFile = "vipConstValues.cfg";

    romDataParsedStatus[2].romConstType = ROM_TYPE_GIP_CONST_VALUES;
    romDataParsedStatus[2].variantCfgFile = "gipConstValues.cfg";

    romDataParsedStatus[3].romConstType = ROM_TYPE_VIP_CONST_TABLES;
    romDataParsedStatus[3].variantCfgFile = "vipConstTables.cfg";

    romDataParsedStatus[4].romConstType = ROM_TYPE_VIP_CONST_MAPS;
    romDataParsedStatus[4].variantCfgFile = "vipConstMaps.cfg";

    for(index = 0;index < MAX_ROM_CONST_TYPES;index++)
    {
        romDataParsedStatus[index].parsedStatus = false;
    }
}

/*******************************************************************************
 Function Name     : setRomConstParsedStatus

 Description       : Sets the ROM CONST parsed status.

 Parameters        : Type of ROM CONST

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void setRomConstParsedStatus(uint8_t romDataType)
{
    if(romDataType < MAX_ROM_CONST_TYPES)
    {
        romDataParsedStatus[romDataType].parsedStatus = true;
    }
}

/*******************************************************************************
 Function Name     : resetRomConstParsedStatus

 Description       : Clears the ROM CONST parsed status.

 Parameters        : Type of ROM CONST

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void resetRomConstParsedStatus(uint8_t romDataType)
{
    if(romDataType < MAX_ROM_CONST_TYPES)
    {
        romDataParsedStatus[romDataType].parsedStatus = false;
    }
}

/*******************************************************************************
 Function Name     : getRomConstParsedStatus

 Description       : Gets the ROM CONST parsed status.

 Parameters        : Type of ROM CONST

 Return Value      : Pointer to ROM CONST parsed status data structure.

 Critical Section  : None
 *******************************************************************************/
ROM_CONST_PARSED_STATUS* getRomConstParsedStatus(uint8_t romDataType)
{
    if(romDataType < MAX_ROM_CONST_TYPES)
    {
        return (&romDataParsedStatus[romDataType]);
    }
    else
    {
        return NULL;
    }
}
/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
void printQListVipConstValueContents(QList<ROM_DATA_VIP_CONST_VALUES> const& vipConstValue)
{
    QList<ROM_DATA_VIP_CONST_VALUES>::const_iterator listIter;

    for(listIter = vipConstValue.begin();listIter != vipConstValue.end();++listIter)
    {
        ROM_DATA_VIP_CONST_VALUES vipConstValueIndex = *listIter;
        qDebug()<<"Name - "<<vipConstValueIndex.name;
        qDebug()<<"Min Value - "<<vipConstValueIndex.scaling.minValue;
        qDebug()<<"Max Value - "<<vipConstValueIndex.scaling.maxValue;
        qDebug()<<"Resolution - "<<QString::number(vipConstValueIndex.scaling.resolution, 'g',10) ;
        qDebug()<<"Units - "<<vipConstValueIndex.scaling.units;
        QMapIterator<QString, QString> iter(vipConstValueIndex.variantValue);

        while(iter.hasNext())
        {
            iter.next();
            qDebug() << iter.key() << " : " << iter.value();
        }
    }
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
void printQListGipConstValueContents(QList<ROM_DATA_GIP_CONST_VALUES> const& gipConstValue)
{
    QList<ROM_DATA_GIP_CONST_VALUES>::const_iterator listIter;
    qDebug()<<"*********************** GIP CONST VALUES ***********************";

    for(listIter = gipConstValue.begin();listIter != gipConstValue.end();++listIter)
    {
        ROM_DATA_GIP_CONST_VALUES gipConstValueIndex = *listIter;
        qDebug()<<"Name - "<<gipConstValueIndex.name;
        qDebug()<<"Min Value - "<<gipConstValueIndex.scaling.minValue;
        qDebug()<<"Max Value - "<<gipConstValueIndex.scaling.maxValue;
        qDebug()<<"Resolution - "<<QString::number(gipConstValueIndex.scaling.resolution, 'g',10) ;
        qDebug()<<"Units - "<<gipConstValueIndex.scaling.units;
        QMapIterator<QString, QString> iter(gipConstValueIndex.variantValue);

        while(iter.hasNext())
        {
            iter.next();
            qDebug() << iter.key() << " : " << iter.value();
        }
    }
}

/*******************************************************************************
 Function Name     : JlrXmlParser::processVipConstantValueTag

 Description       : Initiates the processing for all of the
                     VIP CONST VALUE constants and updates the parsing status.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::processVipConstantValueTag(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("VIP_ConstantValues"));
    ERROR_CODES_T errorCode = ERR_OK;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "VIP_ConstantValues") && !(xml.hasError()))

    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name().startsWith("CONST_"))
            {
                parseVipConstValueElements(xml);
            }
        }
        xml.readNext();
    }

    if(xml.hasError())
    {
        errorCode = ERR_VIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        /* Successfully parsed and loaded the VIP CONST VALUE contents
         * to the internal data structure.
         * Update parsed status for VIP CONST VALUES.
         */
        setRomConstParsedStatus(ROM_TYPE_VIP_CONST_VALUES);
    }

    return errorCode;
}


/*******************************************************************************
 Function Name     : JlrXmlParser::processGipConstantEnums

 Description       : Initiates the processing for all of the
                     GIP CONST VALUE constants and updates the parsing status.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::processGipConstantValueTag(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("GIP_ConstantValues"));
    ERROR_CODES_T errorCode = ERR_OK;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "GIP_ConstantValues") && !(xml.hasError()))

    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name().startsWith("CONST_"))
            {
                parseGipConstValueElements(xml);
            }
        }
        xml.readNext();
    }

    if(xml.hasError())
    {
        errorCode = ERR_GIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        /* Successfully parsed and loaded the GIP CONST VALUE contents
         * to the internal data structure.
         * Update parsed status for GIP CONST VALUES.
         */
        setRomConstParsedStatus(ROM_TYPE_GIP_CONST_VALUES);
    }

    return errorCode;
}


/*******************************************************************************
 Function Name     : JlrXmlParser::processGipConstantEnums

 Description       : Initiates the processing for all of the
                     GIP CONST VALUE constants and updates the parsing status.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::processVipConstantTablesTag(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("VIP_ConstantTables"));
    ERROR_CODES_T errorCode = ERR_OK;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "VIP_ConstantTables") && !(xml.hasError()))

    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if((xml.name().startsWith("CONST_")) || (xml.name().startsWith("Speed")))
            {
                parseVipConstantTablesElements(xml);
            }
        }
        xml.readNext();
    }

    if(xml.hasError())
    {
        errorCode = ERR_VIP_CONST_TABLES_XML_PARSING_FAILED;
    }
    else
    {
        /* Successfully parsed and loaded the VIP CONST TABLES contents
         * to the internal data structure.
         * Update parsed status for VIP CONST TABLES.
         */
        setRomConstParsedStatus(ROM_TYPE_VIP_CONST_TABLES);
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumTable

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     all of the sub fields in VIP ENUM constants into internal
                     data structure.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::parseVipConstValueElements(QXmlStreamReader &xml)
{
    ERROR_CODES_T errorCode = ERR_OK;
    const QString constName = xml.name().toString();
    ROM_DATA_VIP_CONST_VALUES vipConstValue;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == constName) && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name().toString() == constName)
                {
                    vipConstValue.name = xml.name().toString();
                }
                else if(xml.name() == "Group")
                {
                    vipConstValue.group = xml.readElementText();
                }
                else if(xml.name() == "Domain")
                {
                    /* Skip 'Domain' tag as we're not interested in the domain data now.
                     * The next version of tool can perform some additional error
                     * checking on the constant values with the value given in the
                     * 'Domain' tag.
                     */
                }
                else if(xml.name() == "Scaling")
                {
                    updateScalingFactorsVipConstValues(xml,&vipConstValue);
                }
                else if(xml.name() == "Value")
                {
                    updateVipConstValueVariantValues(xml,&vipConstValue);
                }
                else
                {

                }
            }
            xml.readNext();
        }
        romDataConstVipValuesList.append(vipConstValue);
    }

    return errorCode;
}


/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumTable

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     all of the sub fields in VIP ENUM constants into internal
                     data structure.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::parseGipConstValueElements(QXmlStreamReader &xml)
{
    ERROR_CODES_T errorCode = ERR_OK;
    const QString constName = xml.name().toString();
    ROM_DATA_GIP_CONST_VALUES gipConstValue;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_GIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == constName) && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name().toString() == constName)
                {
                    gipConstValue.name = xml.name().toString();
                }
                else if(xml.name() == "Group")
                {
                    gipConstValue.group = xml.readElementText();
                }
                else if(xml.name() == "Domain")
                {
                    /* Skip 'Domain' tag as we're not interested in the domain data now.
                     * The next version of tool can perform some additional error
                     * checking on the constant values with the value given in the
                     * 'Domain' tag.
                     */
                }
                else if(xml.name() == "Scaling")
                {
                    updateScalingFactorsGipConstValues(xml,&gipConstValue);
                }
                else if(xml.name() == "Value")
                {
                    updateGipConstValueVariantValues(xml,&gipConstValue);
                }
                else
                {

                }
            }
            xml.readNext();
        }
        romDataConstGipValuesList.append(gipConstValue);
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumTable

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     all of the sub fields in VIP ENUM constants into internal
                     data structure.

 Parameters        : QXmlStreamReader object

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::parseVipConstantTablesElements(QXmlStreamReader &xml)
{
    ERROR_CODES_T errorCode = ERR_OK;
    const QString constName = xml.name().toString();
    ROM_DATA_VIP_CONST_TABLES vipConstTable;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_TABLES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == constName) && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name().toString() == constName)
                {
                    vipConstTable.name = xml.name().toString();
                    qDebug()<<vipConstTable.name;
                }
                else if(xml.name() == "Group")
                {
                    vipConstTable.group = xml.readElementText();
                    qDebug()<<vipConstTable.group;
                }
                else if(xml.name() == "Length")
                {
                    vipConstTable.length = xml.readElementText().toShort();
                    qDebug()<<vipConstTable.length;
                }
                else if(false != isCurrentVariantPresentInVariantList(xml.name().toUtf8()))
                {
                    /* The variant in table data is present in variant list */
                    qDebug()<<"VARIANT - "<<xml.name();
                    updateVariantSpecificValueForVipConstTables(xml,xml.name().toUtf8(),&vipConstTable);
                }
//                else if(xml.name() == "Scaling")
//                {
//                    //updateScalingFactorsGipConstValues(xml,&gipConstValue);
//                }
//                else if(xml.name() == "Value")
//                {
//                    //updateGipConstValueVariantValues(xml,&gipConstValue);
//                }
//                else
//                {
//
//                }
            }
            xml.readNext();
        }
        romDataConstVipTablesList.append(vipConstTable);
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::isCurrentVariantPresentInVariantList

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
bool JlrXmlParser::isCurrentVariantPresentInVariantList(QString const& variant)
{
    bool status = false;
    QStringList::const_iterator constIterator;

    for (constIterator = romDataInfo.variantList.constBegin(); constIterator != romDataInfo.variantList.constEnd();\
         ++constIterator)
    {
        if(variant == (*constIterator).toLocal8Bit().constData())
        {
            /* Matched with a variant in variant list */
            status = true;
            break;
        }
    }

    return status;
}
/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::updateVipConstValueVariantValues(QXmlStreamReader &xml,ROM_DATA_VIP_CONST_VALUES* vipConstValue)
{
    ERROR_CODES_T errorCode = ERR_OK;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == "Value") && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() != "Value")
                {
                    vipConstValue->variantValue.insert(xml.name().toString(),xml.readElementText());
                }
            }
            xml.readNext();
        }
    }

    return errorCode;
}


/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::updateGipConstValueVariantValues(QXmlStreamReader &xml,ROM_DATA_GIP_CONST_VALUES* gipConstValue)
{
    ERROR_CODES_T errorCode = ERR_OK;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_GIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == "Value") && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() != "Value")
                {
                    gipConstValue->variantValue.insert(xml.name().toString(),xml.readElementText());
                }
            }
            xml.readNext();
        }
    }

    return errorCode;
}


/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::updateScalingFactorsVipConstValues(QXmlStreamReader &xml,ROM_DATA_VIP_CONST_VALUES* vipConstValue)
{
    ERROR_CODES_T errorCode = ERR_OK;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == "Scaling") && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() != "Scaling")
                {
                    if(xml.name() == "Min_Value")
                    {
                        vipConstValue->scaling.minValue = xml.readElementText().toInt();
                    }
                    else if(xml.name() == "Max_Value")
                    {
                        vipConstValue->scaling.maxValue = xml.readElementText().toLong();
                    }
                    else if(xml.name() == "Resolution")
                    {
                        vipConstValue->scaling.resolution = xml.readElementText().toFloat();
                    }
                    else if(xml.name() == "Units")
                    {
                        vipConstValue->scaling.units = xml.readElementText();
                    }
                    else
                    {

                    }
                }
            }
            xml.readNext();
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::updateScalingFactorsGipConstValues(QXmlStreamReader &xml,ROM_DATA_GIP_CONST_VALUES* gipConstValue)
{
    ERROR_CODES_T errorCode = ERR_OK;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_GIP_CONST_VALUES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == "Scaling") && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() != "Scaling")
                {
                    if(xml.name() == "Min")
                    {
                        gipConstValue->scaling.minValue = xml.readElementText().toInt();
                    }
                    else if(xml.name() == "Max")
                    {
                        gipConstValue->scaling.maxValue = xml.readElementText().toLong();
                    }
                    else if(xml.name() == "Resolution")
                    {
                        gipConstValue->scaling.resolution = xml.readElementText().toFloat();
                    }
                    else if(xml.name() == "Units")
                    {
                        gipConstValue->scaling.units = xml.readElementText();
                    }
                    else
                    {

                    }
                }
            }
            xml.readNext();
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : JlrXmlParser::updateVipConstEnumConstValues

 Description       : Parses the VIP CONST ENUM tags from JLR XML and updates
                     the values for each constants.

 Parameters        : QXmlStreamReader object,
                     Pointer to internal data structure

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T JlrXmlParser::updateVariantSpecificValueForVipConstTables(QXmlStreamReader &xml,\
                                                                        QString const& variant,\
                                                                        ROM_DATA_VIP_CONST_TABLES* vipConstTable)
{
    ERROR_CODES_T errorCode = ERR_OK;

    /* We need a start element */
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
        errorCode = ERR_VIP_CONST_TABLES_XML_PARSING_FAILED;
    }
    else
    {
        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == variant) && !(xml.hasError()))
        {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                qDebug()<<xml.name();
            }
            xml.readNext();
        }
    }

    return errorCode;
}

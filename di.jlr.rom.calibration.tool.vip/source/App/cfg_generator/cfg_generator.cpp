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
** File Name        : cfg_generator.cpp
**
** Author           : Anil Joseph
**
** Description      : Class implementaion for cfg generator module
**
** Organization     : Driver Information Software Section,
**                    DI Core Engineering Department
**
**============================================================================*/

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QString>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <math.h>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "error_handler/error_codes.h"
#include "cfg_generator/cfg_generator.h"
#include "rom_data_type/rom_data_types.h"
#include "jlr_xml_parser/jlr_xml_parser.h"

/*******************************************************************************
 Function Name     : CfgGenerator::setSelectedVariant

 Description       : Sets the selected variant.

 Parameters        : QString const& variant

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void CfgGenerator::setSelectedVariant(QString const& variant)
{
    selectedVariant = variant;
}

/*******************************************************************************
 Function Name     : CfgGenerator::setSelectedVariant

 Description       : Sets the selected variant.

 Parameters        : QString const& variant

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::setupOutputDirectory(const QStringList &variantList)
{
    ERROR_CODES_T errorCode = ERR_OK;

    errorCode = createVariantSpecificFolders(variantList,selectedVariant);

    return errorCode;
}
/*******************************************************************************
 Function Name     : CfgGenerator::createVariantSpecificFolders

 Description       : Creates the variant specific CFG folders

 Parameters        : QStringList const& variantList

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::createVariantSpecificFolders(QStringList const&\
                                                         variantList,\
                                                         QString variantSelected)
{
    ERROR_CODES_T errorCode = ERR_OK;
    (void)variantList;

    if(selectedVariant != "All")
    {
        QDir cfgGenDir;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        cfgFolderPath += variantSelected.toLower()+"/";

        /* Generate CFG files for all types of constants */
        uint8_t index = 0;

        for(index = 0;index<MAX_ROM_CONST_TYPES;index++)
        {
            /* Check whether the parsing is completed for the particular
             * ROM data constant.
             */
            if(getRomConstParsedStatus(index)->parsedStatus == true)
            {
                /* Set the cfg file name based on the ROM const data type */
                QString CfgFileName = "cfg_rom_const_";
                QFile cfgFile;
                CfgFileName += getRomConstParsedStatus(index)->variantCfgFile;
                cfgFile.setFileName(cfgFolderPath + CfgFileName);

                if(!cfgGenDir.exists(cfgFolderPath))
                {
                    if(false != cfgGenDir.mkpath(cfgFolderPath))
                    {
                        if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text)))
                        {
                            errorCode = ERR_FAILED_TO_CREATE_VARIANT_CFG_TEMPLATE;
                        }
                        else
                        {
                            errorCode = updateTemplateTextToCfgFile(cfgFolderPath +\
                                                                    CfgFileName);
                        }
                    }
                    else
                    {
                        errorCode = ERR_FAILED_TO_CREATE_VARIANT_FOLDER;
                    }
                }
                else
                {
                    cfgGenDir.remove(cfgFolderPath + CfgFileName);
                    cfgGenDir.rmdir(cfgFolderPath);

                    if(false != cfgGenDir.mkpath(cfgFolderPath))
                    {
                        if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text)))
                        {
                            errorCode = ERR_FAILED_TO_CREATE_VARIANT_CFG_TEMPLATE;
                        }
                        else
                        {
                            errorCode = updateTemplateTextToCfgFile(cfgFolderPath +\
                                                                    CfgFileName);
                        }
                    }
                    else
                    {
                        errorCode = ERR_FAILED_TO_CREATE_VARIANT_FOLDER;
                    }
                }
            }
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateCfgFileWithRomConstantData

 Description       : Updates the CFG files with the ROM constant data parsed from
                     the JLR XML file.

 Parameters        : QStringList const& variantList

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateCfgFileWithRomConstantData(class JlrXmlParser* xmlParser)
{
    ERROR_CODES_T errorCode = ERR_OK;

    qDebug()<<"Selected variant - "<<selectedVariant;

    if(selectedVariant != "All")
    {
        uint8_t index = 0;

        for(index = 0;index<MAX_ROM_CONST_TYPES;index++)
        {
            /* Check whether the parsing is completed for the particular
             * ROM data constant.
             */
            switch(index)
            {
                case ROM_TYPE_VIP_CONST_ENUMS:
                {
                    errorCode = updateRomDataForVipConstEnumsToCfgFile(xmlParser);
                }
                break;

                case ROM_TYPE_VIP_CONST_VALUES:
                {
                    errorCode = updateRomDataForVipConstValuesToCfgFile(xmlParser);
                }
                break;

                case ROM_TYPE_GIP_CONST_VALUES:
                {
                    errorCode = updateRomDataForGipConstValuesToCfgFile(xmlParser);
                }
                break;

                case ROM_TYPE_VIP_CONST_TABLES:
                {
                	errorCode = updateRomDataForVipConstTableToCfgFile(xmlParser);
                }
                break;

                case ROM_TYPE_VIP_CONST_MAPS:
                {

                }
                break;
            }
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateRomDataForVipConstEnumsToCfgFile

 Description       : Updates the ROM constant data for VIP constant enums
                     into the CFG file.

 Parameters        : class JlrXmlParser

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateRomDataForVipConstEnumsToCfgFile(class JlrXmlParser *xmlParser)
{
    ERROR_CODES_T errorCode = ERR_OK;

    if(getRomConstParsedStatus(ROM_TYPE_VIP_CONST_ENUMS)->parsedStatus == true)
    {
        QList<ROM_DATA_VIP_CONST_ENUMS>::const_iterator listIter;
        QFile cfgFile;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        QString CfgFileName = "cfg_rom_const_vipConstEum.cfg";

        CfgFileName = cfgFolderPath + selectedVariant.toLower() + "/" + CfgFileName;
        cfgFile.setFileName(CfgFileName);

        if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)))
        {
            errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
        }
        else
        {
            QTextStream out(&cfgFile);

            for(listIter = xmlParser->romDataConstVipEnumList.begin();listIter != xmlParser->romDataConstVipEnumList.end();++listIter)
            {
                ROM_DATA_VIP_CONST_ENUMS romDataIndex = *listIter;
                QString cfgWriteLine = "#define ";
                cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                               + "(" + romDataIndex.variant[selectedVariant]+ ")" + "\r\n";
                out<<cfgWriteLine;
                cfgWriteLine.clear();
            }
            out<<"#endif";
            cfgFile.flush();
            cfgFile.close();
            qDebug()<<"Generated CFG file for "<<selectedVariant;
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateRomDataForVipConstValuesToCfgFile

 Description       : Updates the ROM constant data for VIP constant values
                     into the CFG file.

 Parameters        : class JlrXmlParser

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateRomDataForVipConstValuesToCfgFile(class JlrXmlParser *xmlParser)
{
	ERROR_CODES_T errorCode = ERR_OK;

    if(getRomConstParsedStatus(ROM_TYPE_VIP_CONST_VALUES)->parsedStatus == true)
    {
        QList<ROM_DATA_VIP_CONST_VALUES>::const_iterator listIter;
        QFile cfgFile;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        QString CfgFileName = "cfg_rom_const_vipConstValues.cfg";

        CfgFileName = cfgFolderPath + selectedVariant.toLower() + "/" + CfgFileName;
        cfgFile.setFileName(CfgFileName);

        if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)))
        {
            errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
        }
        else
        {
            QTextStream out(&cfgFile);

            for(listIter = xmlParser->romDataConstVipValuesList.begin();listIter != xmlParser->romDataConstVipValuesList.end();++listIter)
            {
                ROM_DATA_VIP_CONST_VALUES romDataIndex = *listIter;

                if(romDataIndex.name != "CONST_ROM_Page_PartNumber")
                {
                    /* Make sure the constant values are well within the limits
                     * specified in scaling data
                     */
                    if(romDataIndex.scaling.resolution != 0)
                    {
                        float_t resolutionRounded = (roundf((romDataIndex.scaling.resolution)*100000)/100000);
                        int32_t variantValueDerived = int32_t((romDataIndex.variantValue[selectedVariant].toInt())/
                                                              (resolutionRounded));

                        QString cfgWriteLine = "#define ";
                        cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                       + "(" + QString::number(variantValueDerived)+ ")" + "\r\n";
                        out<<cfgWriteLine;
                        cfgWriteLine.clear();


                        /*
                         * The additional error checking for verifying whether the constant value is well within the
                         * limits of min and max value is disabled for now as the data from JLR XML is not meeting
                         * the above criteria. Need to check with JLR.
                         */
#if 0
                        if((romDataIndex.variantValue[selectedVariant].toInt() >= romDataIndex.scaling.minValue) &&
                           (romDataIndex.variantValue[selectedVariant].toInt() <= romDataIndex.scaling.maxValue))
                        {
                            int32_t variantValueDerived = ((romDataIndex.variantValue[selectedVariant].toDouble())/
                                                           (romDataIndex.scaling.resolution));

                            QString cfgWriteLine = "#define ";
                            cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                           + "(" + QString::number(variantValueDerived)+ ")" + "\r\n";
                            out<<cfgWriteLine;
                            cfgWriteLine.clear();
                        }
                        else
                        {
                           qDebug()<<"ERROR: VIP CONST VALUE OUT OF RANGE - "<<romDataIndex.name;
                           qDebug()<<"Min Value - "<<romDataIndex.scaling.minValue;
                           qDebug()<<"Max Value - "<<romDataIndex.scaling.maxValue;
                           qDebug()<<"Variant value - "<<romDataIndex.variantValue[selectedVariant];
                           qDebug()<<"****************************************************************************";
                           errorCode = ERR_VIP_CONST_VALUE_OUT_OF_RANGE;
                        }
#endif
                    }
                    else
                    {
                        int32_t variantValueDerived = (romDataIndex.variantValue[selectedVariant].toDouble());

                        QString cfgWriteLine = "#define ";
                        cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                       + "(" + QString::number(variantValueDerived)+ ")" + "\r\n";
                        out<<cfgWriteLine;
                        cfgWriteLine.clear();
                    }

                }
            }
            out<<"#endif";
            cfgFile.flush();
            cfgFile.close();
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateRomDataForGipConstValuesToCfgFile

 Description       : Updates the ROM constant data for GIP constant values
                     into the CFG file.

 Parameters        : class JlrXmlParser

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateRomDataForGipConstValuesToCfgFile(class JlrXmlParser *xmlParser)
{
    ERROR_CODES_T errorCode = ERR_OK;

    if(getRomConstParsedStatus(ROM_TYPE_GIP_CONST_VALUES)->parsedStatus == true)
    {
        QList<ROM_DATA_GIP_CONST_VALUES>::const_iterator listIter;
        QFile cfgFile;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        QString CfgFileName = "cfg_rom_const_gipConstValues.cfg";

        CfgFileName = cfgFolderPath + selectedVariant.toLower() + "/" + CfgFileName;
        cfgFile.setFileName(CfgFileName);

        if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)))
        {
            errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
        }
        else
        {
            QTextStream out(&cfgFile);

            for(listIter = xmlParser->romDataConstGipValuesList.begin();listIter != xmlParser->romDataConstGipValuesList.end();++listIter)
            {
                ROM_DATA_GIP_CONST_VALUES romDataIndex = *listIter;

                if(romDataIndex.name != "CONST_ROM_Page_PartNumber")
                {
                    /* Make sure the constant values are well within the limits
                     * specified in scaling data
                     */
                    if(romDataIndex.scaling.resolution != 0)
                    {
                        float_t resolutionRounded = (roundf((romDataIndex.scaling.resolution)*100000)/100000);
                        int32_t variantValueDerived = int32_t((romDataIndex.variantValue[selectedVariant].toInt())/
                                                              (resolutionRounded));

                        QString cfgWriteLine = "#define ";
                        cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                       + "(" + QString::number(variantValueDerived)+ ")" + "\r\n";
                        out<<cfgWriteLine;
                        cfgWriteLine.clear();


                        /*
                         * The additional error checking for verifying whether the constant value is well within the
                         * limits of min and max value is disabled for now as the data from JLR XML is not meeting
                         * the above criteria. Need to check with JLR.
                         */
#if 0
                        if((romDataIndex.variantValue[selectedVariant].toInt() >= romDataIndex.scaling.minValue) &&
                           (romDataIndex.variantValue[selectedVariant].toInt() <= romDataIndex.scaling.maxValue))
                        {
                            int32_t variantValueDerived = ((romDataIndex.variantValue[selectedVariant].toDouble())/
                                                           (romDataIndex.scaling.resolution));

                            QString cfgWriteLine = "#define ";
                            cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                           + "(" + QString::number(variantValueDerived)+ ")" + "\r\n";
                            out<<cfgWriteLine;
                            cfgWriteLine.clear();
                        }
                        else
                        {
                           qDebug()<<"ERROR: VIP CONST VALUE OUT OF RANGE - "<<romDataIndex.name;
                           qDebug()<<"Min Value - "<<romDataIndex.scaling.minValue;
                           qDebug()<<"Max Value - "<<romDataIndex.scaling.maxValue;
                           qDebug()<<"Variant value - "<<romDataIndex.variantValue[selectedVariant];
                           qDebug()<<"****************************************************************************";
                           errorCode = ERR_VIP_CONST_VALUE_OUT_OF_RANGE;
                        }
#endif
                    }
                    else
                    {
                        int32_t variantValueDerived = (romDataIndex.variantValue[selectedVariant].toDouble());

                        QString cfgWriteLine = "#define ";
                        cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                       + "(" + QString::number(variantValueDerived)+ ")" + "\r\n";
                        out<<cfgWriteLine;
                        cfgWriteLine.clear();
                    }

                }
            }
            out<<"#endif";
            cfgFile.flush();
            cfgFile.close();
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateRomDataForGipConstValuesToCfgFile

 Description       : Updates the ROM constant data for GIP constant values
                     into the CFG file.

 Parameters        : class JlrXmlParser

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateRomDataForVipConstTableToCfgFile(class JlrXmlParser *xmlParser)
{
    ERROR_CODES_T errorCode = ERR_OK;

    if(getRomConstParsedStatus(ROM_TYPE_VIP_CONST_TABLES)->parsedStatus == true)
    {
        QList<ROM_DATA_VIP_CONST_TABLES>::const_iterator listIter;
        QFile cfgFile;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        QString CfgFileName = "cfg_rom_const_vipConstTables.cfg";

        CfgFileName = cfgFolderPath + selectedVariant.toLower() + "/" + CfgFileName;

        populateVipConstTableDataInCfgFile(CfgFileName,xmlParser->romDataConstVipTablesList);

    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateTemplateTextToCfgFile

 Description       : Updates the Visteon header file template to CFG files.

 Parameters        : QString const& fileName

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::populateVipConstTableDataInCfgFile(QString const& cfgFileName,\
		                            QList<ROM_DATA_VIP_CONST_TABLES> const& vipConstTable)
{
	ERROR_CODES_T errorCode = ERR_OK;
	QList<ROM_DATA_VIP_CONST_TABLES>::const_iterator listIter;

    for(listIter = vipConstTable.begin();listIter != vipConstTable.end();++listIter)
    {
        updateVipConstTableCfgTemplateToCfgFile(cfgFileName);
        ROM_DATA_VIP_CONST_TABLES vipConstTableValueIndex = *listIter;
        //qDebug()<<"Name - "<<vipConstTableValueIndex.name;
    }



#if 0
	if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)))
    {
        errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
    }
    else
    {
        for(listIter = vipConstTable.begin();listIter != vipConstTable.end();++listIter)
        {
            updateVipConstTableCfgTemplateToCfgFile(cfgFileName);
        	ROM_DATA_VIP_CONST_TABLES vipConstTableValueIndex = *listIter;
            qDebug()<<"Name - "<<vipConstTableValueIndex.name;

//            qDebug()<<"Input Scaling Min value - "<<vipConstTableValueIndex.InputScaling.minValue;
//            qDebug()<<"Input Scaling Max value - "<<vipConstTableValueIndex.InputScaling.maxValue;
//            qDebug()<<"Input Scaling Resolution - "<<QString::number(vipConstTableValueIndex.InputScaling.resolution, 'g',10);
//            qDebug()<<"Input Scaling Units - "<<vipConstTableValueIndex.InputScaling.units;
//
//            qDebug()<<"Output Scaling Min value - "<<vipConstTableValueIndex.OutputScaling.minValue;
//            qDebug()<<"Output Scaling Max value - "<<vipConstTableValueIndex.OutputScaling.maxValue;
//            qDebug()<<"Output Scaling Resolution - "<<QString::number(vipConstTableValueIndex.OutputScaling.resolution, 'g',10);
//            qDebug()<<"Output Scaling Units - "<<vipConstTableValueIndex.OutputScaling.units;
//
//            for(const VIP_CONST_TABLE_DATA & value: vipConstTableValueIndex.TableData)
//            {
//                qDebug()<<value.variant<<" : "<<value.index<<" : "<<value.inputValue<<" : "<<value.outputValue;
//            }
        }

    }
#endif

	 return errorCode;
}
/*******************************************************************************
 Function Name     : CfgGenerator::updateTemplateTextToCfgFile

 Description       : Updates the Visteon header file template to CFG files.

 Parameters        : QString const& fileName

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateTemplateTextToCfgFile(QString const& fileName)
{
    ERROR_CODES_T errorCode = ERR_OK;

    QFile cfgTemplateFile("../source/cfg_template.cfg");
    QFile cfgFile(fileName);

    if(!(cfgTemplateFile.open(QFile::ReadOnly | QFile::Text)))
    {
        errorCode = ERR_FAILED_TO_OPEN_CFG_TEMPLATE_FILE;
    }
    else
    {
        QTextStream cfgTemplateContent(&cfgTemplateFile);
        QString text = cfgTemplateContent.readAll();

        if(!cfgFile.open(QFile::WriteOnly | QFile::Text | QIODevice::Append))
        {
            errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
        }
        else
        {
            QTextStream out(&cfgFile);
            out<<text;
            cfgFile.flush();
            cfgFile.close();
        }
        cfgTemplateFile.close();
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateTemplateTextToCfgFile

 Description       : Updates the Visteon header file template to CFG files.

 Parameters        : QString const& fileName

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateVipConstTableCfgTemplateToCfgFile(QString const& fileName)
{
    ERROR_CODES_T errorCode = ERR_OK;

    QFile cfgTemplateFile("../source/vipConstTableFormat.txt");
    QFile cfgFile(fileName);

    if(!(cfgTemplateFile.open(QFile::ReadOnly | QFile::Text)))
    {
        errorCode = ERR_FAILED_TO_OPEN_CFG_TEMPLATE_FILE;
        qDebug()<<"ERR_FAILED_TO_OPEN_CFG_TEMPLATE_FILE";
    }
    else
    {
        QTextStream cfgTemplateContent(&cfgTemplateFile);
        QString text = cfgTemplateContent.readAll();

        if(!cfgFile.open(QFile::WriteOnly | QFile::Text | QFile::Append))
        {
            errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
            qDebug()<<"ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE";
        }
        else
        {
            QTextStream out(&cfgFile);
            out<<text;
            cfgFile.flush();
            cfgFile.close();
        }
        cfgTemplateFile.close();
    }

    return errorCode;
}

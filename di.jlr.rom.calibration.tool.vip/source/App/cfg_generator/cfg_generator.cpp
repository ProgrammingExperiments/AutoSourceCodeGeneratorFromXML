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

    if(selectedVariant != "All")
    {
        QDir cfgGenDir;
        QFile cfgFile;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        QString CfgFileName = "cfg_rom_const_";
        cfgFolderPath += selectedVariant.toLower()+"/";

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
    else
    {
        for(QStringList::const_iterator listIterator = variantList.begin();listIterator\
            != variantList.end();++listIterator)
        {
            QDir cfgGenDir;
            QFile cfgFile;
            QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
            QString CfgFileName = "cfg_rom_const_";
            QString variantIndex = *listIterator;
            cfgFolderPath += variantIndex.toLower() +"/";

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

    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : CfgGenerator::updateCfgFileWithCfgData

 Description       : Updates the CFG files with the ROM constant data parsed from
                     the JLR XML file.

 Parameters        : QStringList const& variantList

 Return Value      : Error Code

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T CfgGenerator::updateCfgFileWithCfgData(QList<ROM_DATA_VIP_CONST_ENUMS>\
                                                     const& romData,\
                                                     QStringList const& variantList)
{
    ERROR_CODES_T errorCode = ERR_OK;

    qDebug()<<"Total No. of VIP ENUM constants - "<<romData.length();
    qDebug()<<"Selected variant - "<<selectedVariant;

    if(selectedVariant != "All")
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

            for(listIter = romData.begin();listIter != romData.end();++listIter)
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
    else
    {
        QList<ROM_DATA_VIP_CONST_ENUMS>::const_iterator listIter;
        QFile cfgFile;
        QString cfgFolderPath = "../output/cfg_files/di.jlr.rom.const.";
        QString CfgFileName = "cfg_rom_const_vipConstEum.cfg";

        for(QStringList::const_iterator listIterator = variantList.begin();\
            listIterator != variantList.end();++listIterator)
        {
            QString variantIndex = *listIterator;

            CfgFileName = cfgFolderPath + variantIndex.toLower() + "/" + CfgFileName;
            cfgFile.setFileName(CfgFileName);

            if (!(cfgFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)))
            {
                errorCode = ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE;
            }
            else
            {
                QTextStream out(&cfgFile);

                for(listIter = romData.begin();listIter != romData.end();++listIter)
                {
                    ROM_DATA_VIP_CONST_ENUMS romDataIndex = *listIter;
                    QString cfgWriteLine = "#define ";
                    cfgWriteLine = cfgWriteLine + romDataIndex.name + "_VALUE  " + \
                                   + "(" + romDataIndex.variant[variantIndex]+ ")" + "\r\n";
                    out<<cfgWriteLine;
                    cfgWriteLine.clear();
                }
                out<<"#endif";
                cfgFile.flush();
                cfgFile.close();
                qDebug()<<"Generated CFG file for "<<selectedVariant<<" variants";
            }
        }
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

        if(!cfgFile.open(QFile::WriteOnly | QFile::Text))
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

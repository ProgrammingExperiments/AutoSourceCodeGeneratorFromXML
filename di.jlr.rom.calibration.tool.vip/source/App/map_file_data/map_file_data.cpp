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
** File Name        : map_file_data.cpp
**
** Author           : Anil Joseph
**
** Description      : Class implementation for MAP file data
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
#include <QTextStream>
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

using namespace std;
/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T MapDataContents::importMapFileData(QFile & mapFile)
{
    ERROR_CODES_T errorCode = ERR_OK;

    QString mapDataString;

    QTextStream in(&mapFile);

    while (!in.atEnd())
    {
       QString line = in.readLine();

       if(line.contains("0x"))
       {
           mapDataString.append(line + "\n");
       }
    }

    mapFile.resize(0);
    in << mapDataString;
    mapFile.close();

    return errorCode;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T MapDataContents::processMapDataFileByLine(QString & line)
{
    ERROR_CODES_T errorCode = ERR_OK;
    QString startString("ROM items");
    static bool bStartStringFound = false;
    static uint32_t lineIndex = 0;
    MAP_DATA_FILE mapDataImported;

    if (line.contains(startString, Qt::CaseSensitive))
    {
        bStartStringFound = true;
        lineIndex = 4;
    }
    else
    {
        if(bStartStringFound != false)
        {
            lineIndex++;

            if(lineIndex >= 6)
            {
                line.replace(QRegExp("[\\s\\n]+"), " ");

                QRegExp rx("[, ]");// match a comma or a space
                QStringList list = line.split(rx, QString::SkipEmptyParts);

                qDebug()<<"Constant Name - "<<list.at(0);
                qDebug()<<"Constant Address - "<<list.at(1);
                qDebug()<<"Constant Length - "<<list.at(2);

                mapDataImported.constName    = list.at(0);
                mapDataImported.constAddress = list.at(1);
                mapDataImported.constSize    = list.at(2);
                qDebug()<<"\r\n";
            }
        }
    }

    return errorCode;
}

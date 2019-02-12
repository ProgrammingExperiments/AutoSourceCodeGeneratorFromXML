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
** Description      : Class implementation for VBF Generator
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
#include <QDir>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "jlr_xml_parser/jlr_xml_parser.h"
#include "main_window/main_window.h"
#include "error_handler/error_codes.h"
#include "vbf_generator/vbf_generator.h"
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
ERROR_CODES_T RomBlockDataFile::importRomBlockDataFile(const QString &romFileName)
{
    ERROR_CODES_T errorCode = ERR_OK;

    QFile romDataFileObj(romFileName);

    romBlockSrecordList.clear();

    if(!romDataFileObj.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Error - Unable to open ROM constant data file.";
    }
    else
    {
        QTextStream in(&romDataFileObj);

        while (!in.atEnd())
        {
           QString line = in.readLine();
           readRomBlockDataFileContents(line);
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T RomBlockDataFile::readRomBlockDataFileContents(QString const& romBlockLine)
{
    ERROR_CODES_T errorCode = ERR_OK;

    if ((romBlockLine.contains("S0", Qt::CaseSensitive)) ||
        (romBlockLine.contains("S2", Qt::CaseSensitive)) ||
        (romBlockLine.contains("S8", Qt::CaseSensitive)))
    {
        parseSRecordLine(romBlockLine);
    }

    return errorCode;

}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
SREC_ERROR_TYPE RomBlockDataFile::parseSRecordLine(const QString &romBlockLine)
{
    SREC_ERROR_TYPE errorType = SRECORD_OK;

    ROM_BLOCK_SRECORD romBlockSRecordData;

    /* Parse the S-RECORD type */
    readSRecordType(&romBlockSRecordData,romBlockLine.at(SREC_TYPE_INDEX));

    /* Parse the Byte Counts */
    readByteCount(&romBlockSRecordData,romBlockLine);

    /* Parse the S-Record address */
    readAddress(&romBlockSRecordData,romBlockLine);

    /* Parse the ROM data */
    readRomData(&romBlockSRecordData,romBlockLine);

    /* Parse the S-Record line checksum */
    readChecksum(&romBlockSRecordData,romBlockLine);

    /* Copy the parsed S-RECORD data into internal data structure */
    romBlockSrecordList.append(romBlockSRecordData);

    return errorType;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
SREC_ERROR_TYPE RomBlockDataFile::readSRecordType(ROM_BLOCK_SRECORD* romBlockRecord,\
                                                    const QString &recordType)
{
    SREC_ERROR_TYPE errorType = SRECORD_OK;

    /* check for the S-Record type */
    if((recordType == SREC_TYPE_S0) ||
       (recordType == SREC_TYPE_S2) ||
       (recordType == SREC_TYPE_S8))
    {
        if(recordType == SREC_TYPE_S0)
        {
            romBlockRecord->type = SRECORD_TYPE_S0;
        }
        else if(recordType == SREC_TYPE_S2)
        {
            romBlockRecord->type = SRECORD_TYPE_S2;
        }
        else if(recordType == SREC_TYPE_S8)
        {
           romBlockRecord->type = SRECORD_TYPE_S8;
        }
        else
        {

        }
    }
    else
    {
        errorType = SRECORD_ERROR_FAILED_TO_IDENTIFY_REC_TYPE;
        qDebug()<<"SRECORD_ERROR_FAILED_TO_IDENTIFY_REC_TYPE";
    }

    return errorType;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
SREC_ERROR_TYPE RomBlockDataFile::readByteCount(ROM_BLOCK_SRECORD *romBlockRecord,\
                                                  const QString &romBlockLine)
{
    SREC_ERROR_TYPE errorType = SRECORD_OK;

    QString byteCountQString = romBlockLine.mid(SREC_BYTE_COUNT_START_INDEX,\
                                              ((SREC_BYTE_COUNT_END_INDEX - \
                                                SREC_BYTE_COUNT_START_INDEX) + 1));

    /* convert Qstring data to QByteArray */
    QByteArray byteCountByteArray = byteCountQString.toLocal8Bit();

    /* Convert HEX string to long int and store it in data structure */
    romBlockRecord->byteCount = (int32_t)strtol(byteCountByteArray.data(), NULL, 16);

    return errorType;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
SREC_ERROR_TYPE RomBlockDataFile::readAddress(ROM_BLOCK_SRECORD *romBlockRecord,\
                                                  const QString &romBlockLine)
{
    SREC_ERROR_TYPE errorType = SRECORD_OK;

    /* Read address only if it's S2 record */
    if(romBlockRecord->type == SRECORD_TYPE_S2)
    {
        romBlockRecord->address = romBlockLine.mid(SREC_ADDRESS_START_INDEX,\
                                                  ((SREC_ADDRESS_END_INDEX - \
                                                    SREC_ADDRESS_START_INDEX) + 1));
    }
    else
    {
        if(romBlockRecord->type == SRECORD_TYPE_S0)
        {
            uint8_t addressEndIndex = (SREC_ADDRESS_END_INDEX - 2);
            romBlockRecord->address = romBlockLine.mid(SREC_ADDRESS_START_INDEX,\
                                                      ((addressEndIndex - \
                                                        SREC_ADDRESS_START_INDEX) + 1));
        }
        else if(romBlockRecord->type == SRECORD_TYPE_S8)
        {
            romBlockRecord->address = romBlockLine.mid(SREC_ADDRESS_START_INDEX,\
                                                      ((SREC_ADDRESS_END_INDEX - \
                                                        SREC_ADDRESS_START_INDEX) + 1));
        }
        else
        {

        }
    }

    return errorType;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
SREC_ERROR_TYPE RomBlockDataFile::readRomData(ROM_BLOCK_SRECORD *romBlockRecord,\
                                                  const QString &romBlockLine)
{
    SREC_ERROR_TYPE errorType = SRECORD_OK;

    /* Read ROM data only if it's S2 record */
    if(romBlockRecord->type == SRECORD_TYPE_S2)
    {
        romBlockRecord->romData = romBlockLine.mid(SREC_DATA_START_INDEX,\
                                                  ((SREC_DATA_END_INDEX - \
                                                    SREC_DATA_START_INDEX) + 1));
    }
    else
    {
        /* Update rom data field as NULL for S0 & S8 records */
        romBlockRecord->romData.clear();
    }

    return errorType;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
SREC_ERROR_TYPE RomBlockDataFile::readChecksum(ROM_BLOCK_SRECORD *romBlockRecord,\
                                                  const QString &romBlockLine)
{
    SREC_ERROR_TYPE errorType = SRECORD_OK;

    if(romBlockRecord->type == SRECORD_TYPE_S2)
    {
        QString checksumQString = romBlockLine.mid(SREC_CHECKSUM_START_INDEX,\
                                                  ((SREC_CHECKSUM_END_INDEX - \
                                                    SREC_CHECKSUM_START_INDEX) + 1));

        /* convert Qstring data to QByteArray */
        QByteArray checksumByteArray = checksumQString.toLocal8Bit();

        /* Convert HEX string to long int and store it in data structure */
        romBlockRecord->checksum = (int32_t)strtol(checksumByteArray.data(), NULL, 16);
    }
    else
    {
        if(romBlockRecord->type == SRECORD_TYPE_S0)
        {
            QString checksumQString = romBlockLine.mid(8,2);

            /* convert Qstring data to QByteArray */
            QByteArray checksumByteArray = checksumQString.toLocal8Bit();

            /* Convert HEX string to long int and store it in data structure */
            romBlockRecord->checksum = (int32_t)strtol(checksumByteArray.data(), NULL, 16);
        }
        else if(romBlockRecord->type == SRECORD_TYPE_S8)
        {
            QString checksumQString = romBlockLine.mid(10,2);

            /* convert Qstring data to QByteArray */
            QByteArray checksumByteArray = checksumQString.toLocal8Bit();

            /* Convert HEX string to long int and store it in data structure */
            romBlockRecord->checksum = (int32_t)strtol(checksumByteArray.data(), NULL, 16);
        }
        else
        {

        }
    }

    return errorType;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void RomBlockDataFile::printRomBlockDataContents(QList<ROM_BLOCK_SRECORD> const& romBlockSRecord)
{
    QList<ROM_BLOCK_SRECORD>::const_iterator listIter;

    for(listIter = romBlockSRecord.begin();listIter != romBlockSRecord.end();++listIter)
    {
        ROM_BLOCK_SRECORD romBlockData = *listIter;

        qDebug()<<"Type        - "<<romBlockData.type;
        qDebug()<<"Byte Counts - "<<romBlockData.byteCount;
        qDebug()<<"Address     - "<<romBlockData.address;
        qDebug()<<"Data        - "<<romBlockData.romData;
        qDebug()<<"Checksum    - "<<romBlockData.checksum;
        qDebug()<<"";
    }
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
ERROR_CODES_T RomBlockDataFile::createRomBlockDataBinaryFile(void)
{
    ERROR_CODES_T errorCode = ERR_OK;
    QDir romDataOutputDir;
    QFile romDataOutputFile;
    QString romDataOutputFilePath = "../output/rom_data_file/";
    QString romDataOutputFileName = romDataOutputFilePath + "rom_data_file.ROMBLOCK";
    romDataOutputFile.setFileName(romDataOutputFileName);

    if(!romDataOutputDir.exists(romDataOutputFilePath))
    {
        if(false != romDataOutputDir.mkpath(romDataOutputFilePath))
        {
            if (!(romDataOutputFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)))
            {
                errorCode = ERR_FAILED_TO_OPEN_ROM_DATA_OP_FILE;
            }
            else
            {
                QTextStream out(&romDataOutputFile);

                QList<ROM_BLOCK_SRECORD>::iterator listIter;

                for(listIter = romBlockSrecordList.begin();listIter != romBlockSrecordList.end();++listIter)
                {
                    ROM_BLOCK_SRECORD romDataFileIndex = *listIter;
                    QString byteCountString = (QString("%1").arg(romDataFileIndex.byteCount,2, 16, QLatin1Char( '0' )));
                    QString checksumString  = (QString("%1").arg(romDataFileIndex.checksum,2, 16, QLatin1Char( '0' )));

                    QString romDataLine = "S" + QString::number(romDataFileIndex.type) +\
                                          byteCountString +\
                                          romDataFileIndex.address +\
                                          romDataFileIndex.romData +\
                                          checksumString +\
                                          "\n";

                    out<<romDataLine;
                    romDataLine.clear();
                }

                romDataOutputFile.flush();
                romDataOutputFile.close();
            }
        }
    }
    else
    {
        romDataOutputDir.remove(romDataOutputFileName);
        romDataOutputDir.rmdir(romDataOutputFilePath);

        if(false != romDataOutputDir.mkpath(romDataOutputFilePath))
        {
            if (!(romDataOutputFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)))
            {
                errorCode = ERR_FAILED_TO_OPEN_ROM_DATA_OP_FILE;
            }
            else
            {
                QTextStream out(&romDataOutputFile);

                QList<ROM_BLOCK_SRECORD>::iterator listIter;

                for(listIter = romBlockSrecordList.begin();listIter != romBlockSrecordList.end();++listIter)
                {
                    ROM_BLOCK_SRECORD romDataFileIndex = *listIter;
                    QString byteCountString = (QString("%1").arg(romDataFileIndex.byteCount,2, 16, QLatin1Char( '0' )));
                    QString checksumString  = (QString("%1").arg(romDataFileIndex.checksum,2, 16, QLatin1Char( '0' )));

                    QString romDataLine = "S" + QString::number(romDataFileIndex.type) +\
                                          byteCountString.toUpper() +\
                                          romDataFileIndex.address +\
                                          romDataFileIndex.romData +\
                                          checksumString.toUpper() +\
                                          "\n";

                    out<<romDataLine;
                    romDataLine.clear();
                }

                romDataOutputFile.flush();
                romDataOutputFile.close();
            }
        }
    }

    return errorCode;
}

/*******************************************************************************
 Function Name     : xxxx

 Description       : xxxx

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
QString& convertIntToHexString(uint8_t length,int32_t integerValue)
{
    static QString hexValue;

    hexValue.append(QString("%1").arg(integerValue,length, 16, QLatin1Char( '0' )));
    return hexValue;
}

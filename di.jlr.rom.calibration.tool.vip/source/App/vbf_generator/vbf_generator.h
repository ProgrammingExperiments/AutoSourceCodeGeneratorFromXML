/*============================================================================
*                                                                            *
*              CONFIDENTIAL VISTEON CORPORATION                              *
*                                                                            *
* This is an unpublished work of authorship, which contains trade            *
* secrets, created in 2018. Visteon Corporation owns all rights to           *
* this work and intends to maintain it in confidence to preserve             *
* its trade secret status. Visteon Corporation reserves the right,           *
* under the copyright laws of the United States or those of any              *
* other country that may have jurisdiction, to protect this work             *
* as an unpublished work, in the event of an inadvertent or                  *
* deliberate unauthorized publication. Visteon Corporation also              *
* reserves its rights under all copyright laws to protect this               *
* work as a published work, when appropriate. Those having access            *
* to this work may not copy it, use it, modify it or disclose the            *
* information contained in it without the written authorization              *
* of Visteon Corporation.                                                    *
*                                                                            *
**============================================================================
**
**  File Name    : map_file_data.h
**
**  Author       : Anil Joseph
**
**  Description  : Class definition for MAP file data module.
**
**  Organization : Driver Information Software Section,
**                 DI Core Engineering Department
**
**===========================================================================*/
#ifndef VBF_GENERATOR
#define VBF_GENERATOR

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QFile>
#include <QXmlStreamReader>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "main_window/main_window.h"
#include "rom_data_type/rom_data_types.h"
#include "error_handler/error_codes.h"

/*==========================================================================*/
/*                            Macro definitions                              */
/*==========================================================================*/
#define SREC_TYPE_INDEX             (1)
#define SREC_BYTE_COUNT_START_INDEX (2)
#define SREC_BYTE_COUNT_END_INDEX   (3)
#define SREC_ADDRESS_START_INDEX    (4)
#define SREC_ADDRESS_END_INDEX      (9)
#define SREC_DATA_START_INDEX       (10)
#define SREC_DATA_END_INDEX         (41)
#define SREC_CHECKSUM_START_INDEX   (42)
#define SREC_CHECKSUM_END_INDEX     (43)

#define SREC_TYPE_S0            ('0')
#define SREC_TYPE_S2            ('2')
#define SREC_TYPE_S8            ('8')
/*==========================================================================*/
/*                            Type definitions                              */
/*==========================================================================*/

/* General definition of the S-Record specification */
typedef enum
{
    /* 768 should be plenty of space to read in an S-Record */
    SRECORD_RECORD_BUFF_SIZE = 800,
    /* Offsets and lengths of various fields in an S-Record record */
    SRECORD_TYPE_OFFSET = 1,
    SRECORD_TYPE_LEN = 1,
    SRECORD_COUNT_OFFSET = 2,
    SRECORD_COUNT_LEN = 2,
    SRECORD_ADDRESS_OFFSET = 4,
    SRECORD_CHECKSUM_LEN = 2,
    /* Maximum ascii hex length of the S-Record data field */
    SRECORD_MAX_DATA_LEN = 254*2,
    /* Maximum ascii hex length of the S-Record address field */
    SRECORD_MAX_ADDRESS_LEN = 8,
    /* Ascii hex length of a single byte */
    SRECORD_ASCII_HEX_BYTE_LEN = 2,
    /* Start code offset and value */
    SRECORD_START_CODE_OFFSET = 0,
    SRECORD_START_CODE = 'S',
}SREC_DEFINITIONS;

/*  All possible error codes, S-Record utility functions may return */
typedef enum
{
    SRECORD_OK = 0,
    SRECORD_ERROR_FILE = -1,
    SRECORD_ERROR_EOF = -2,
    SRECORD_ERROR_INVALID_RECORD = -3,
    SRECORD_ERROR_INVALID_ARGUMENTS = -4,
    SRECORD_ERROR_NEWLINE = -5,
    SRECORD_ERROR_FAILED_TO_IDENTIFY_REC_TYPE = -6,
}SREC_ERROR_TYPE;

/*  Types of SREC type */
typedef enum
{
    SRECORD_TYPE_S0 = 0,
    SRECORD_TYPE_S2 = 2,
    SRECORD_TYPE_S8 = 8,
}SREC_TYPE;

/* Structure to hold the fields of a ROM block S-Record data */
typedef struct
{
    QString address;
    QString romData;
    int32_t byteCount;
    SREC_TYPE type;
    int32_t checksum;
}ROM_BLOCK_SRECORD;


/*==========================================================================*/
/*                              Class Definitions                           */
/*==========================================================================*/
class RomBlockDataFile
{
public:
    /* Member functions */
    ERROR_CODES_T importRomBlockDataFile(QString const& romFileName);

    ERROR_CODES_T readRomBlockDataFileContents(QString const& romBlockLine);

    SREC_ERROR_TYPE parseSRecordLine(const QString &romBlockLine);

    SREC_ERROR_TYPE readSRecordType(ROM_BLOCK_SRECORD* romBlockRecord,\
                                    const QString &recordType);

    SREC_ERROR_TYPE readByteCount(ROM_BLOCK_SRECORD* romBlockRecord,\
                                  const QString &romBlockLine);

    SREC_ERROR_TYPE readAddress(ROM_BLOCK_SRECORD *romBlockRecord,\
                                const QString &romBlockLine);

    SREC_ERROR_TYPE readRomData(ROM_BLOCK_SRECORD *romBlockRecord,\
                                const QString &romBlockLine);

    SREC_ERROR_TYPE readChecksum(ROM_BLOCK_SRECORD *romBlockRecord,\
                                                      const QString &romBlockLine);

    void printRomBlockDataContents(QList<ROM_BLOCK_SRECORD> const& romBlockSRecord);

    ERROR_CODES_T createRomBlockDataBinaryFile(void);

    /* Data Structures */
    QList<ROM_BLOCK_SRECORD> romBlockSrecordList;

private:
};

/*==========================================================================*/
/*                               Function Prototypes                        */
/*==========================================================================*/
QString& convertIntToHexString(uint8_t length,int32_t integerValue);

#endif // VBF_GENERATOR

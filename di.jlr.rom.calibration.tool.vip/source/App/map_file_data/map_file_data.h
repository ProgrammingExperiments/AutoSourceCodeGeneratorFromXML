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
#ifndef MAP_FILE_DATA
#define MAP_FILE_DATA

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
/*                            Macro Definitions                             */
/*==========================================================================*/


/*==========================================================================*/
/*                              Class Definitions                           */
/*==========================================================================*/
class MapDataContents
{
public:
    /* Member functions */
    MapDataContents(void);
    ERROR_CODES_T importMapFileData(QString const& cfgFileName);
    ERROR_CODES_T removeEmptyLinesInMapFile(QFile & mapFile);
    ERROR_CODES_T processMapDataFileByLine(QString & line);
    void printMapDataContents(void);

    /* Data Structures */
    QList<MAP_DATA_FILE> romConstMapFileDataList;

private:
};

/*==========================================================================*/
/*                               Function Prototypes                        */
/*==========================================================================*/


#endif // MAP_FILE_DATA

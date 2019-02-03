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
**  File Name    : rom_data_type.h
**
**  Author       : Anil Joseph
**
**  Description  : Class definition for GUI main window
**
**  Organization : Driver Information Software Section,
**                 DI Core Engineering Department
**
**===========================================================================*/
#ifndef ROM_DATA_TYPES_H
#define ROM_DATA_TYPES_H

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QString>
#include <QMap>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include <stdint.h>

/******************************************************************************
 *                      INTERNAL ROM CONSTANT DATA STRUCTURES                 *
 ******************************************************************************/
/******************************************************************************
 * 3 main tags from JLR XML are,
 *
 * 1. Information
 * 2. VIP_ConstantEnums
 * 3. VIP_ConstantValues
 * 4. GIP_ConstantValues
 * 5. VIP_ConstantTables
 * 6. VIP_ConstantMaps
 ******************************************************************************/
/*=============================================================================
 * ROM CONST TYPES ENUM
 *=============================================================================*/
typedef enum
{
    ROM_TYPE_VIP_CONST_ENUMS = 0,
    ROM_TYPE_VIP_CONST_VALUES,
    ROM_TYPE_GIP_CONST_VALUES,
    ROM_TYPE_VIP_CONST_TABLES,
    ROM_TYPE_VIP_CONST_MAPS
}ROM_CONST_TYPES_T;

/*=============================================================================
 * ROM CONST TYPES - PARSED STATUS
 *=============================================================================*/
typedef struct
{
    ROM_CONST_TYPES_T romConstType;
    bool parsedStatus;
    QString variantCfgFile;
}ROM_CONST_PARSED_STATUS;

/*=============================================================================
 * ROM CONST DATA - SCALING
 *=============================================================================*/
typedef struct
{
    int32_t minValue;
    uint32_t maxValue;
    double_t resolution;
    QString units;
}ROM_CONST_SCALING_DATA;

/*=============================================================================
 * VIP CONSTANT TABLE - TABLE DATA
 *=============================================================================*/
typedef struct
{
    QString variant;
    uint16_t index;
    QString inputValue;
    QString outputValue;
}VIP_CONST_TABLE_DATA;

/*=============================================================================
 * Information
 *=============================================================================*/
typedef struct
{
    QStringList variantList;
    QString version;
}ROM_DATA_INFO;

/*=============================================================================
 * VIP Constant Enums
 *=============================================================================*/
typedef struct
{
    QString name;
    QString group;
    QMap<QString,QString> variant;
}ROM_DATA_VIP_CONST_ENUMS;

/*=============================================================================
 * VIP Constant Values
 *=============================================================================*/
typedef struct
{
    QString name;
    QString group;
    ROM_CONST_SCALING_DATA scaling;
    QMap<QString,QString> variantValue;
}ROM_DATA_VIP_CONST_VALUES;

/*=============================================================================
 * GIP Constant Values
 *=============================================================================*/
typedef struct
{
    QString name;
    QString group;
    ROM_CONST_SCALING_DATA scaling;
    QMap<QString,QString> variantValue;
}ROM_DATA_GIP_CONST_VALUES;

/*=============================================================================
 * VIP Constant Tables
 *=============================================================================*/
typedef struct
{
    QString name;
    QString group;
    uint16_t length;
    ROM_CONST_SCALING_DATA InputScaling;
    ROM_CONST_SCALING_DATA OutputScaling;
    QMap<QString,VIP_CONST_TABLE_DATA> TableData;
}ROM_DATA_VIP_CONST_TABLES;

/*=============================================================================
 * MAP Data File
 *=============================================================================*/
typedef struct
{
    QString constName;
    QString constAddress;
    QString constSize;
}MAP_DATA_FILE;

/*=============================================================================
 * VIP CONST TABLE - MIN MAX VALUES
 *=============================================================================*/
typedef struct
{
    int32_t minValue;
    int32_t maxValue;

}MIN_MAX_INPUT_SCALING;

#endif // ROM_DATA_TYPES_H

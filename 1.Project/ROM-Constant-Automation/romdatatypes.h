#ifndef ROMDATATYPES_H
#define ROMDATATYPES_H

#include <stdint.h>
#include <QString>
#include <QMap>

#include "typedefine.h"

/*
 * 3 main tags from JLR XML are,
 *
 * 1. Information
 * 2. VIP_ConstantEnums
 * 3. VIP_ConstantValues
 * 4. GIP_ConstantValues
 * 5. VIP_ConstantTables
 * 6. VIP_ConstantMaps
 */

/*================================================================================
 * Information
 *================================================================================*/
typedef struct
{
    QStringList variantList;
    QString version;
}ROM_DATA_INFO;

/*================================================================================
 * VIP Constant Enums
 *================================================================================*/
typedef struct
{
    QString name;
    QString group;
    QMap<QString,QString> variant;
    uint32_t constCount;
}ROM_DATA_VIP_CONST_ENUMS;

/*================================================================================
 * ROM DATA STRUCTURE
 *================================================================================*/
//typedef struct
//{
//    ROM_DATA_INFO info; /* <Information> */
//    ROM_DATA_VIP_CONST_ENUMS vipConstEnums; /* <VIP_ConstantEnums> */


//}ROM_DATA_STRUCTURES;

#endif // ROMDATATYPES_H

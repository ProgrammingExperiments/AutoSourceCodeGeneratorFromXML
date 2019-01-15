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
**  File Name    : cfg_generator.h
**
**  Author       : Anil Joseph
**
**  Description  : Class definition for cfg_generator module.
**
**  Organization : Driver Information Software Section,
**                 DI Core Engineering Department
**
**===========================================================================*/
#ifndef CFG_GENERATOR_H
#define CFG_GENERATOR_H

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QString>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "rom_data_type/rom_data_types.h"
#include "error_handler/error_codes.h"

/*==========================================================================*/
/*                              Class Definitions                           */
/*==========================================================================*/
class CfgGenerator
{
private:
    QString selectedVariant;

public:
    void setSelectedVariant(QString const& variant);
    ERROR_CODES_T setupOutputDirectory(QStringList const& variantList);
    ERROR_CODES_T createVariantSpecificFolders(QStringList const& variantList,QString variantSelected);
    ERROR_CODES_T updateCfgFileWithRomConstantData(class JlrXmlParser* xmlParser);
    ERROR_CODES_T updateRomDataForVipConstEnumsToCfgFile(class JlrXmlParser* xmlParser);
    ERROR_CODES_T updateRomDataForVipConstValuesToCfgFile(class JlrXmlParser* xmlParser);
    ERROR_CODES_T updateRomDataForGipConstValuesToCfgFile(class JlrXmlParser* xmlParser);
    ERROR_CODES_T updateTemplateTextToCfgFile(QString const& fileName);
};

#endif // CFG_GENERATOR_H

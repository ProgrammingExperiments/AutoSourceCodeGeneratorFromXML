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
**  File Name    : jlr_xml_parser.h
**
**  Author       : Anil Joseph
**
**  Description  : Class definition for JLR XML Parser module.
**
**  Organization : Driver Information Software Section,
**                 DI Core Engineering Department
**
**===========================================================================*/
#ifndef JLR_XML_PARSER_H
#define JLR_XML_PARSER_H

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
#define MAX_ROM_CONST_TYPES (5)

/*==========================================================================*/
/*                              Class Definitions                           */
/*==========================================================================*/
class JlrXmlParser
{
public:
    JlrXmlParser(void);
    bool read(QIODevice *device);
    ERROR_CODES_T readXML(void);

    /* Member functions for parsing <Information> tag */
    void processXmlInformation(QXmlStreamReader &xml);

    /* Member functions for parsing <VIP_ConstantEnums> tag */
    ERROR_CODES_T processVipConstantEnumTag(QXmlStreamReader &xml);
    ERROR_CODES_T parseVipConstEnumElements(QXmlStreamReader& xml);
    ERROR_CODES_T updateVipConstEnumVariantValues(QXmlStreamReader &xml,\
                                                ROM_DATA_VIP_CONST_ENUMS*\
                                                vipConstEnum);

    /* Member functions for parsing <VIP_ConstantValues> tag */
    ERROR_CODES_T processVipConstantValueTag(QXmlStreamReader &xml);
    ERROR_CODES_T parseVipConstValueElements(QXmlStreamReader& xml);
    ERROR_CODES_T updateScalingFactorsVipConstValues(QXmlStreamReader &xml,\
                                                     ROM_DATA_VIP_CONST_VALUES*\
                                                     vipConstValue);
    ERROR_CODES_T updateVipConstValueVariantValues(QXmlStreamReader &xml,\
                                                ROM_DATA_VIP_CONST_VALUES*\
                                                vipConstValue);

    /* Member functions for parsing <GIP_ConstantValues> tag */
    ERROR_CODES_T processGipConstantValueTag(QXmlStreamReader &xml);
    ERROR_CODES_T parseGipConstValueElements(QXmlStreamReader& xml);
    ERROR_CODES_T updateScalingFactorsGipConstValues(QXmlStreamReader &xml,\
                                                     ROM_DATA_GIP_CONST_VALUES*\
                                                     gipConstValue);
    ERROR_CODES_T updateGipConstValueVariantValues(QXmlStreamReader &xml,\
                                                ROM_DATA_GIP_CONST_VALUES*\
                                                gipConstValue);

    /* Member functions for parsing <VIP_ConstantTables> tag */
    ERROR_CODES_T processVipConstantTablesTag(QXmlStreamReader &xml);
    ERROR_CODES_T parseVipConstantTablesElements(QXmlStreamReader& xml);
    bool isCurrentVariantPresentInVariantList(QString const& variant);
    ERROR_CODES_T updateVariantSpecificValueForVipConstTables(QXmlStreamReader &xml,\
                                                              QString const& variant,\
                                                              ROM_DATA_VIP_CONST_TABLES*\
                                                              vipConstTable);

    void UpdateVariantInfo(QString const& variantData);
    void UpdateXmlVersion(const QString &xmlVersion);
    static inline QString versionAttribute() {return QStringLiteral("version");}

    ROM_DATA_INFO romDataInfo;
    QList<ROM_DATA_VIP_CONST_ENUMS> romDataConstVipEnumList;
    QList<ROM_DATA_VIP_CONST_VALUES> romDataConstVipValuesList;
    QList<ROM_DATA_GIP_CONST_VALUES> romDataConstGipValuesList;
    QList<ROM_DATA_VIP_CONST_TABLES> romDataConstVipTablesList;

private:
   QXmlStreamReader jlrXml;
   QFile *jlrFile;
};

/*==========================================================================*/
/*                               Function Prototypes                        */
/*==========================================================================*/
ROM_CONST_PARSED_STATUS* getRomConstParsedStatus(uint8_t romDataType);
void printQListVipConstValueContents(QList<ROM_DATA_VIP_CONST_VALUES>\
                                     const& vipConstValue);
void printQListGipConstValueContents(QList<ROM_DATA_GIP_CONST_VALUES>\
                                     const& gipConstValue);
void setRomConstParsedStatus(uint8_t romDataType);
void resetRomConstParsedStatus(uint8_t romDataType);
void resetRomConstParsedStatus(void);

#endif // JLR_XML_PARSER_H

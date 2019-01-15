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
**  File Name    : error_codes.h
**
**  Author       : Anil Joseph
**
**  Description  : Error code data definitions
**
**  Organization : Driver Information Software Section,
**                 DI Core Engineering Department
**
**===========================================================================*/
#ifndef ERROR_CODES_H
#define ERROR_CODES_H


/*==========================================================================*/
/*                            Type Definitions                              */
/*==========================================================================*/
typedef enum
{
    ERR_OK = 0,
    ERR_UNABLE_TO_LOAD_JLR_XML,
    ERR_UNABLE_TO_READ_JLR_XML,
    ERR_VIP_CONST_ENUM_XML_PARSING_FAILED,
    ERR_VIP_CONST_VALUES_XML_PARSING_FAILED,
    ERR_GIP_CONST_VALUES_XML_PARSING_FAILED,
    ERR_VIP_CONST_TABLES_XML_PARSING_FAILED,
    ERR_VIP_CONST_MAPS_XML_PARSING_FAILED,
    ERR_FAILED_TO_CREATE_VARIANT_FOLDER,
    ERR_FAILED_TO_CREATE_VARIANT_CFG_TEMPLATE,
    ERR_FAILED_TO_CREATE_FINAL_VARIANT_CFG,
    ERR_FAILED_TO_OPEN_CFG_TEMPLATE_FILE,
    ERR_FAILED_TO_OPEN_VARIANT_CFG_FILE,
    ERR_VIP_CONST_VALUE_OUT_OF_RANGE,
}ERROR_CODES_T;



#endif // ERROR_CODES_H

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

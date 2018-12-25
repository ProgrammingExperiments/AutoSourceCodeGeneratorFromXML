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
** File Name        : main.cpp
**
** Author           : Anil Joseph
**
** Description      : Starting point of the rom calibration tool
**
** Organization     : Driver Information Software Section,
**                    DI Core Engineering Department
**
**============================================================================*/

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QApplication>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "main_window/main_window.h"

/*******************************************************************************
 Function Name     : main

 Description       : Starting point for the application

 Parameters        : command line arguments

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
int main(int argc, char *argv[])
{
    QApplication gui_app(argc, argv);
    MainWindow gui_window;
    gui_window.show();

    return gui_app.exec();
}

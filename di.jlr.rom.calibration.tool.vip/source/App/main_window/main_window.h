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
**  File Name    : main_window.h
**
**  Author       : Anil Joseph
**
**  Description  : Class definition for GUI main window
**
**  Organization : Driver Information Software Section,
**                 DI Core Engineering Department
**
**===========================================================================*/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QMainWindow>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "cfg_generator/cfg_generator.h"
#include "jlr_xml_parser/jlr_xml_parser.h"
#include "map_file_data/map_file_data.h"

/*==========================================================================*/
/*                              Class Definitions                           */
/*==========================================================================*/
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStringList* variantList;
    explicit MainWindow(QWidget *parent = 0);
    void processErrorCodes(ERROR_CODES_T errorCode);
    ~MainWindow();

private slots:
    void on_SelectVariant_comboBox_currentIndexChanged(int index);
    void on_pushButton_GenerateCfg_clicked();

    void on_BrowseXml_PushButton_clicked();

    void on_pushButton_BrowseMap_clicked();

    void on_pushButton_BrowseRomData_clicked();

private:
    Ui::MainWindow *ui;
    class JlrXmlParser *xmlParser;
    class CfgGenerator *cfgGenerator;
    class MapDataContents *mapFileData;
};

#endif // MAIN_WINDOW_H

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
** File Name        : main_window.cpp
**
** Author           : Anil Joseph
**
** Description      : Class implementation for GUI class
**
** Organization     : Driver Information Software Section,
**                    DI Core Engineering Department
**
**============================================================================*/

/******************************************************************************
 *                           Qt Specific Include Files                        *
 ******************************************************************************/
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <qdebug.h>

/******************************************************************************
 *                          Application Specfic Include Files                 *
 ******************************************************************************/
#include "main_window.h"
#include "ui_mainwindow.h"
#include "error_handler/error_codes.h"
#include "jlr_xml_parser/jlr_xml_parser.h"

/*******************************************************************************
 Function Name     : MainWindow::MainWindow

 Description       : Constructor for class MainWindow

 Parameters        : QWidget Object

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xmlParser    = new JlrXmlParser;
    cfgGenerator = new CfgGenerator;
    mapFileData  = new MapDataContents;
}

/*******************************************************************************
 Function Name     : MainWindow::~MainWindow

 Description       : Destructor for class MainWindow

 Parameters        : QWidget Object

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
MainWindow::~MainWindow()
{
    delete xmlParser;
    delete cfgGenerator;
    delete mapFileData;
    delete ui;
}

/*******************************************************************************
 Function Name     : MainWindow::processErrorCodes

 Description       : Provides an error indication to GUI based on the error code.

 Parameters        : errorCode

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void MainWindow::processErrorCodes(ERROR_CODES_T errorCode)
{
    switch(errorCode)
    {
        case ERR_UNABLE_TO_LOAD_JLR_XML:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("Unabled to load JLR XML file"),
                      QMessageBox::Ok);
        }
        break;

        case ERR_UNABLE_TO_READ_JLR_XML:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("Unabled to read JLR XML file"),
                      QMessageBox::Ok);

        }
        break;

        case ERR_VIP_CONST_ENUM_XML_PARSING_FAILED:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("XML parsing failed for VIP constant enums"),
                      QMessageBox::Ok);
        }
        break;

        case ERR_VIP_CONST_VALUES_XML_PARSING_FAILED:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("XML parsing failed for VIP constant values"),
                      QMessageBox::Ok);

        }
        break;

        case ERR_GIP_CONST_VALUES_XML_PARSING_FAILED:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("XML parsing failed for GIP constant values"),
                      QMessageBox::Ok);

        }
        break;

        case ERR_VIP_CONST_TABLES_XML_PARSING_FAILED:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("XML parsing failed for VIP constant tables"),
                      QMessageBox::Ok);

        }
        break;

        case ERR_VIP_CONST_MAPS_XML_PARSING_FAILED:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("XML parsing failed for VIP constant maps"),
                      QMessageBox::Ok);

        }
        break;

        case ERR_FAILED_TO_CREATE_VARIANT_FOLDER:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("Failed to create variant specific folders"),
                      QMessageBox::Ok);
        }
        break;

        case ERR_FAILED_TO_CREATE_VARIANT_CFG_TEMPLATE:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("Failed to create variant cfg file templates"),
                      QMessageBox::Ok);
        }
        break;

        case ERR_FAILED_TO_CREATE_FINAL_VARIANT_CFG:
        {
            QMessageBox::critical(this, tr("Error"),
                      tr("Failed to create final cfg file"),
                      QMessageBox::Ok);
        }
        break;

        default:
        break;
    }
}

/*******************************************************************************
 Function Name     : MainWindow::on_SelectVariant_comboBox_currentIndexChanged

 Description       : Handle for 'Select Variant' combo box.
                     Provides an option for the user to select the variant for
                     which the CFG files and VBF needs to be generated.

 Parameters        : variant index

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void MainWindow::on_SelectVariant_comboBox_currentIndexChanged(int index)
{
    (void)index;
    cfgGenerator->setSelectedVariant(ui->SelectVariant_comboBox->currentText());
}

/*******************************************************************************
 Function Name     : MainWindow::on_pushButton_GenerateCfg_clicked

 Description       : Handle for 'Generate CFG Files' push button.
                     Generates the CFG files and VBF files by processing the data
                     from internal data structures.

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void MainWindow::on_pushButton_GenerateCfg_clicked()
{
    ERROR_CODES_T errorCode = ERR_OK;

    errorCode = cfgGenerator->setupOutputDirectory(xmlParser->romDataInfo.variantList);

    if(errorCode != ERR_OK)
    {
        processErrorCodes(errorCode);
    }
    else
    {
        errorCode = cfgGenerator->updateCfgFileWithRomConstantData(xmlParser);
        qDebug() <<"*********FINISHED**********";
        qDebug()<<"\r\n";
    }
}

/*******************************************************************************
 Function Name     : MainWindow::on_ImportXml_pushButton_clicked

 Description       : Handle for 'Import XML' push button.
                     Uploads the JLR XML into the tool from file system.

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void MainWindow::on_BrowseXml_PushButton_clicked()
{
    uint8_t index = 0;

    /* Show the open XML file window */
    QString jlrXmlFileStr = QFileDialog::getOpenFileName(this,"Browse for the JLR XML file","C://",("XML Files ( *.xml)"));

    if(jlrXmlFileStr.isEmpty())
    {
        QMessageBox::critical(this,"Error","Unable to open JLR XML file");
        //exit(ERR_UNABLE_TO_LOAD_JLR_XML);
    }

    /* Assign it to the file object and open the file in read mode */
    QFile jlrXmlFileObj(jlrXmlFileStr);

    if(!jlrXmlFileObj.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this,"Error","Unable to open JLR XML file");
        //exit(ERR_UNABLE_TO_READ_JLR_XML);
    }
    else
    {
        ui->BrowseXml_lineEdit->setText(jlrXmlFileStr);

        if (!xmlParser->read(&jlrXmlFileObj))
        {
            QMessageBox::warning(this, tr("XML Parser"),
                                 tr("Parse error in file %1:\n\n%2")
                                 .arg(QDir::toNativeSeparators(jlrXmlFileStr),
                                      jlrXmlFileObj.errorString()));
        }
        else
        {
            while(index < xmlParser->romDataInfo.variantList.length())
            {
                ui->SelectVariant_comboBox->addItem(xmlParser->romDataInfo.variantList.value(index));
                index++;
            }

            statusBar()->showMessage(tr("JLR XML file loaded"), 2000);
        }
    }
}

/*******************************************************************************
 Function Name     : MainWindow::on_pushButton_BrowseMap_clicked

 Description       : Handle for 'Browse MAP File' push button.
                     Imports the ROM CONST MAP file into the tool.

 Parameters        : None

 Return Value      : None

 Critical Section  : None
 *******************************************************************************/
void MainWindow::on_pushButton_BrowseMap_clicked()
{
    QString mapDataFileStr = QFileDialog::getOpenFileName(this,"Browse for the ROM constant MAP file","C://",("MAP files ( *.txt)"));

    if(mapDataFileStr.isEmpty())
    {
        QMessageBox::critical(this,"Error","Unable to open ROM constant MAP file");
    }

    /* Assign it to the file object and open the file in read mode */
    QFile mapDataFileObj(mapDataFileStr);

    if(!mapDataFileObj.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this,"Error","Unable to open ROM constant MAP file");
    }
    else
    {
        ui->BrowseMap_LineEdit->setText(mapDataFileStr);

        mapFileData->removeEmptyLinesInMapFile(mapDataFileObj);

        mapFileData->importMapFileData(mapDataFileStr);

        //mapFileData->printMapDataContents();

        qDebug()<<"Successfully imported the MAP file contents to internal data structure";
    }

}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorcodes.h"
#include "jlrxmlparser.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Add elements to the variant selection combo box */
    ui->SelectVariant_comboBox->addItem("All");
    ui->SelectVariant_comboBox->addItem("L560");
    ui->SelectVariant_comboBox->addItem("L405");
    ui->SelectVariant_comboBox->addItem("L462");
    ui->SelectVariant_comboBox->addItem("L494");
    ui->SelectVariant_comboBox->addItem("X590");
    ui->SelectVariant_comboBox->addItem("X761");
    ui->SelectVariant_comboBox->addItem("L551");
    ui->SelectVariant_comboBox->addItem("L550");
    ui->SelectVariant_comboBox->addItem("X540");
    ui->SelectVariant_comboBox->addItem("L663");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ImportXml_pushButton_clicked()
{
    /* Show the open XML file window */
    QString jlrXmlFileStr = QFileDialog::getOpenFileName(this,"Browse the JLR XML file","C://",("XML Files ( *.xml)"));

    if(jlrXmlFileStr.isEmpty())
    {
        QMessageBox::critical(this,"Error","Unable to open JLR XML file");
        exit(ERR_UNABLE_TO_LOAD_JLR_XML);
    }

    /* Assign it to the file object and open the file in read mode */
    QFile jlrXmlFileObj(jlrXmlFileStr);

    if(!jlrXmlFileObj.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this,"Error","Unable to open JLR XML file");
        exit(ERR_UNABLE_TO_READ_JLR_XML);
    }
    else
    {
        ui->ImportXml_lineEdit->setText(jlrXmlFileStr);

        /* Initialize the xml parser object */
        JlrXmlParser xmlParser;

        if (!xmlParser.read(&jlrXmlFileObj))
        {
            QMessageBox::warning(this, tr("XML Parser"),
                                 tr("Parse error in file %1:\n\n%2")
                                 .arg(QDir::toNativeSeparators(jlrXmlFileStr),
                                      jlrXmlFileObj.errorString()));
        }
        else
        {
            statusBar()->showMessage(tr("JLR XML file loaded"), 2000);
        }
    }
}


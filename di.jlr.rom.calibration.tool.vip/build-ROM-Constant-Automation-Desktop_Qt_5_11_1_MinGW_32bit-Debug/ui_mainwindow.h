/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_GenerateCfg;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *SelectVariant_label;
    QComboBox *SelectVariant_comboBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *BrowseXml_lineEdit;
    QPushButton *BrowseXml_PushButton;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_GenerateVbf;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *BrowseMap_LineEdit;
    QPushButton *pushButton_BrowseMap;
    QLabel *label_3;
    QPushButton *pushButton_GenerateRomData;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *BrowseRomData_LineEdit;
    QPushButton *pushButton_BrowseRomData;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(716, 319);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/Images/Icons/AppWindowIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 0, 691, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_GenerateCfg = new QPushButton(groupBox);
        pushButton_GenerateCfg->setObjectName(QStringLiteral("pushButton_GenerateCfg"));
        pushButton_GenerateCfg->setStyleSheet(QLatin1String("font: 75 8pt \"MS Shell Dlg 2\";\n"
"font: 75 8pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(pushButton_GenerateCfg, 2, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        SelectVariant_label = new QLabel(groupBox);
        SelectVariant_label->setObjectName(QStringLiteral("SelectVariant_label"));

        horizontalLayout->addWidget(SelectVariant_label);

        SelectVariant_comboBox = new QComboBox(groupBox);
        SelectVariant_comboBox->setObjectName(QStringLiteral("SelectVariant_comboBox"));

        horizontalLayout->addWidget(SelectVariant_comboBox);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(475, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        BrowseXml_lineEdit = new QLineEdit(groupBox);
        BrowseXml_lineEdit->setObjectName(QStringLiteral("BrowseXml_lineEdit"));

        horizontalLayout_2->addWidget(BrowseXml_lineEdit);

        BrowseXml_PushButton = new QPushButton(groupBox);
        BrowseXml_PushButton->setObjectName(QStringLiteral("BrowseXml_PushButton"));

        horizontalLayout_2->addWidget(BrowseXml_PushButton);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_GenerateVbf = new QPushButton(groupBox_2);
        pushButton_GenerateVbf->setObjectName(QStringLiteral("pushButton_GenerateVbf"));

        gridLayout_2->addWidget(pushButton_GenerateVbf, 2, 3, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        BrowseMap_LineEdit = new QLineEdit(groupBox_2);
        BrowseMap_LineEdit->setObjectName(QStringLiteral("BrowseMap_LineEdit"));

        horizontalLayout_3->addWidget(BrowseMap_LineEdit);

        pushButton_BrowseMap = new QPushButton(groupBox_2);
        pushButton_BrowseMap->setObjectName(QStringLiteral("pushButton_BrowseMap"));

        horizontalLayout_3->addWidget(pushButton_BrowseMap);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        pushButton_GenerateRomData = new QPushButton(groupBox_2);
        pushButton_GenerateRomData->setObjectName(QStringLiteral("pushButton_GenerateRomData"));

        gridLayout_2->addWidget(pushButton_GenerateRomData, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        BrowseRomData_LineEdit = new QLineEdit(groupBox_2);
        BrowseRomData_LineEdit->setObjectName(QStringLiteral("BrowseRomData_LineEdit"));

        horizontalLayout_4->addWidget(BrowseRomData_LineEdit);

        pushButton_BrowseRomData = new QPushButton(groupBox_2);
        pushButton_BrowseRomData->setObjectName(QStringLiteral("pushButton_BrowseRomData"));

        horizontalLayout_4->addWidget(pushButton_BrowseRomData);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 2, 1, 2);


        verticalLayout->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 716, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ROM Caliberation Tool v1.0", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">JLR ROM Calibration Tool v1.0</span></p></body></html>", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "CFG Generation", nullptr));
        pushButton_GenerateCfg->setText(QApplication::translate("MainWindow", "Generate CFG File", nullptr));
        SelectVariant_label->setText(QApplication::translate("MainWindow", "Select Variant", nullptr));
        BrowseXml_PushButton->setText(QApplication::translate("MainWindow", "Browse", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Upload the JLR XML file here", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "VBF Generation", nullptr));
        pushButton_GenerateVbf->setText(QApplication::translate("MainWindow", "Generate VBF File", nullptr));
        pushButton_BrowseMap->setText(QApplication::translate("MainWindow", "Browse", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Upload the MAP file here", nullptr));
        pushButton_GenerateRomData->setText(QApplication::translate("MainWindow", "Generate ROM data File", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Upload ROM data file here", nullptr));
        pushButton_BrowseRomData->setText(QApplication::translate("MainWindow", "Browse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

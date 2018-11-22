#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <jlrxmlparser.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void UpdateSelectVariantComboBox(QString const& variantData);

private slots:
    void on_ImportXml_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStatusBar* status;
};

#endif // MAINWINDOW_H

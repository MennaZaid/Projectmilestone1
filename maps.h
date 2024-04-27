#ifndef MAPS_H
#define MAPS_H
#include"mainwindow.h"
#include<QDialog>

class MainWindow;

namespace Ui {
class Maps;
}

class Maps : public QDialog
{
    Q_OBJECT

public:
    explicit Maps(QWidget *parent = nullptr);

    ~Maps();

private slots:
    void on_pushButtonmap1_clicked();

private:
    MainWindow* mainWindow;
    Ui::Maps *ui;
};

#endif // MAPS_H

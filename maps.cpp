#include "maps.h"
#include "map.h"
#include "ui_maps.h"
#include<QMediaplayer>
#include<QAudioOutput>
#include"Map1.h"
#include"Map2.h"
Maps::Maps(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Maps)
{
    ui->setupUi(this);
    QPixmap background (":/Back/Background.jpeg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
    QPixmap Map1(":/map1/green land.jpg");
    ui->Map1label->setPixmap(Map1);
    QPixmap Map2(":/Ice/GameBG.png");
    ui->Map2label->setPixmap(Map2);

    this->mainWindow = static_cast<MainWindow*>(this->parent());
}

Maps::~Maps()
{
    delete ui;
}


void Maps::on_pushButtonmap1_clicked()
{
    mainWindow->click->play();
    hide();
    Map1* map1 = new Map1();
}


void Maps::on_pushButtonmap2_clicked()
{
    mainWindow->click->play();
    hide();
    Map2* map2 = new Map2();
}


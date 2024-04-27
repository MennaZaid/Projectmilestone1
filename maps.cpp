#include "maps.h"
#include "map.h"
#include "ui_maps.h"
#include<QMediaplayer>
#include<QAudioOutput>

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
    QPixmap Map2(":/map2/desert land.png");
    ui->Map2label->setPixmap(Map2);
    QPixmap Map3(":/map3/ice land.png");
    ui->Map3label->setPixmap(Map3);

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
    Map* map = new Map(this->mainWindow);
}


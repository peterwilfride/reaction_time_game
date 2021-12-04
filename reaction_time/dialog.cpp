#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    int h = ui->image_label->width();
    int w = ui->image_label->height();
    QPixmap pm(":/img/img/help-image.png");
    ui->image_label->setPixmap(pm.scaled(h, w, Qt::KeepAspectRatio));
}

Dialog::~Dialog()
{
    delete ui;
}

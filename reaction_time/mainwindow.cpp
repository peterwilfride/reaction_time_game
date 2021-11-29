#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter shape(this);

    std::uniform_int_distribution<int> width_dist(0+size+10, 570-size-10);
    std::uniform_int_distribution<int> height_dist(0+size+10, 440-size-10);
    std::uniform_int_distribution<int> color_dist(0, 3);

    int rand_x = width_dist(*QRandomGenerator::global());
    int rand_y = height_dist(*QRandomGenerator::global());
    int rand_c = color_dist(*QRandomGenerator::global());

    shape.setRenderHint(QPainter::Antialiasing, true);
    shape.drawRect(QRect(10, 10, 570, 440));

    switch (rand_c) {
        case 0:
            shape.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            break;
        case 1:
            shape.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
            break;
        case 2:
            shape.setBrush(QBrush(Qt::red, Qt::SolidPattern));
            break;
        case 3:
            shape.setBrush(QBrush(Qt::green, Qt::SolidPattern));
            break;
        default:
            break;
    }

    if (flag)
        shape.drawEllipse(rand_x, rand_y, size, size);
}


void MainWindow::on_start_Button_clicked()
{
    flag = true;
    update();
}


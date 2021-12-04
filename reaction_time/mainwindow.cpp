#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QMessageBox>
#include <stdlib.h>
#include <sys/time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(768, 456));
    ui->score_label->setText(QString::number(score));
    ui->health_bar->setValue(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_random()
{
    std::uniform_int_distribution<int> width_dist(10, 570-size);
    std::uniform_int_distribution<int> height_dist(10, 440-size);
    std::uniform_int_distribution<int> color_dist(0, 3);

    rand_x = width_dist(*QRandomGenerator::global());
    rand_y = height_dist(*QRandomGenerator::global());
    rand_c = color_dist(*QRandomGenerator::global());
}

double MainWindow::calculate_mean_value(QList<double>& list_of_times)
{
    double sum = 0.0;
    foreach (double tempo, list_of_times) {
        sum += tempo;
    }
    return sum / list_of_times.size();
}


void MainWindow::on_start_Button_clicked()
{
    calculate_random();
    flag = true;
    update();
    ui->start_Button->setEnabled(false);
    ui->reset_Button->setEnabled(true);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (ui->health_bar->value() == 0) {
        ui->is_end->setText("fim!");
    }

    QPainter shape(this);

    shape.setRenderHint(QPainter::Antialiasing, true);

    shape.drawRect(10, 10, 570, 430);

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

    if(flag) {
        current_color = rand_c;

        gettimeofday(&i_time, NULL); //tempo inicial
        shape.drawEllipse(rand_x, rand_y, size, size);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case 87:
            if (current_color ==  0) {
                qDebug() << char(e->key()) << " : bola azul capturada";
                ui->eval_label->setText("<font color='green'>ACERTOU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() + 10);
                score += 1;
            }else{
                qDebug() << char(e->key()) << " : você errou";
                ui->eval_label->setText("<font color='red'>ERROU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() - 20);
            }
            break;
        case 68:
            if (current_color ==  1) {
                qDebug() << char(e->key()) << " : bola amarela capturada";
                ui->eval_label->setText("<font color='green'>ACERTOU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() + 10);
                score += 1;
            }else{
                qDebug() << char(e->key()) << " : você errou";
                ui->eval_label->setText("<font color='red'>ERROU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() - 20);
            }
            break;
        case 83:
            if (current_color ==  2) {
                qDebug() << char(e->key()) << " : bola vermelho capturada";
                ui->eval_label->setText("<font color='green'>ACERTOU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() + 10);
                score += 1;
            }else{
                qDebug() << char(e->key()) << " : você errou";
                ui->eval_label->setText("<font color='red'>ERROU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() - 20);
            }
            break;
        case 65:
            if (current_color ==  3) {
                qDebug() << char(e->key()) << " : bola verde capturada";
                ui->eval_label->setText("<font color='green'>ACERTOU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() + 10);
                score += 1;
            }else{
                qDebug() << char(e->key()) << " : você errou";
                ui->eval_label->setText("<font color='red'>ERROU!</font>");
                ui->health_bar->setValue(ui->health_bar->value() - 20);
            }
            break;
        default:
            break;
    }

    gettimeofday(&f_time, NULL); //tempo final
    int tmili = (int) (1000 * (f_time.tv_sec - i_time.tv_sec) +
                       (f_time.tv_usec - i_time.tv_usec) / 1000);

    t_mili = (double) tmili / 1000.0; //tempo em segundos

    list_of_times.append(t_mili);

    double mean_time = calculate_mean_value(list_of_times);

    calculate_random();
    update();
    ui->score_label->setText(QString::number(score));
    ui->last_react_time_label->setText(QString::number(t_mili, 'f', 3) + " s");
    ui->mean_time_label->setText(QString::number(mean_time, 'f', 3) + "s");
}


void MainWindow::on_reset_Button_clicked()
{
    score = 0;
    t_mili = 0.0;
    calculate_random();
    flag = false;
    update();

    ui->score_label->setText(QString::number(score));
    ui->last_react_time_label->setText(QString::number(t_mili, 'f', 3) + " s");
    ui->reset_Button->setEnabled(false);
    ui->start_Button->setEnabled(true);
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void calculate_random();
    double calculate_mean_value(QList<double>& list_of_times);
    void update_bar(int value);
    void game_over();

protected:
    virtual void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_start_Button_clicked();

    void on_reset_Button_clicked();

    void on_help_Button_clicked();

private:
    Ui::MainWindow *ui;
    int increase_bar = 10;
    int decrease_bar = -20;
    bool flag = false;
    int count = 0;
    int size = 100;
    int score = 0;
    int rand_x;
    int rand_y;
    int rand_c;
    int current_color;
    struct timeval i_time, f_time;
    double t_mili;
    QList<double> list_of_times;
    double mean_time;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

protected:
    virtual void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_start_Button_clicked();

    void on_reset_Button_clicked();

private:
    Ui::MainWindow *ui;
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
};
#endif // MAINWINDOW_H

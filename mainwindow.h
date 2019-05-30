#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();
    void on_punto_released();
    void unary_operation_pressed();
    void on_clear_released();
    void on_igual_released();
    void binario_operation_pressed();
    void on_LCD_overflow();
};

#endif // MAINWINDOW_H

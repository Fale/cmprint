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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:


private slots:
    void on_actionClienti_triggered();
    void on_actionGrammatura_triggered();
    void on_actionFormato_triggered();
    void on_actionTipo_triggered();
    void on_actionPreventivi_triggered();
};

#endif // MAINWINDOW_H

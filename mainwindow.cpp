#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 La gui è gestita a widget. Ogni volta che se ne mostra uno bisogna nascondere tutti gli altri.

 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_benvenuto->show();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionPreventivi_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->show();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
}

void MainWindow::on_actionTipo_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->show();
    ui->widget_clienti->hide();
}

void MainWindow::on_actionFormato_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->show();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
}

void MainWindow::on_actionGrammatura_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->show();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
}

void MainWindow::on_actionClienti_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->show();
}

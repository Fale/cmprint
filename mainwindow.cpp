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
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();
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
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();
}

void MainWindow::on_actionTipo_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->show();
    ui->widget_clienti->hide();
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();

}

void MainWindow::on_actionFormato_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->show();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();

}

void MainWindow::on_actionGrammatura_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->show();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();

}

void MainWindow::on_actionClienti_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->show();
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->hide();

}

void MainWindow::on_actionSerigrafia_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
    ui->widget_plastificazione->hide();
    ui->widget_serigrafia->show();


}

void MainWindow::on_actionPlastificazione_triggered()
{
    ui->widget_benvenuto->hide();
    ui->widget_preventivi->hide();
    ui->widget_carta_formato->hide();
    ui->widget_carta_grammatura->hide();
    ui->widget_carta_tipo->hide();
    ui->widget_clienti->hide();
    ui->widget_plastificazione->show();
    ui->widget_serigrafia->hide();
}

void MainWindow::on_pushButton_preventivi_clicked()
{
    MainWindow::on_actionPreventivi_triggered();
}

void MainWindow::on_pushButton_clienti_clicked()
{
    MainWindow::on_actionClienti_triggered();
}

void MainWindow::on_pushButton_carta_tipo_clicked()
{
    MainWindow::on_actionTipo_triggered();
}

void MainWindow::on_pushButton_carta_formato_clicked()
{
    MainWindow::on_actionFormato_triggered();
}

void MainWindow::on_pushButton_carta_grammatura_clicked()
{
    MainWindow::on_actionGrammatura_triggered();
}

void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_actionEsci_triggered()
{
    qApp->quit();
}


void MainWindow::on_pushButton_serigrafia_clicked()
{
    MainWindow::on_actionSerigrafia_triggered();
}


void MainWindow::on_pushButton_plastificazione_clicked()
{
    MainWindow::on_actionPlastificazione_triggered();
}

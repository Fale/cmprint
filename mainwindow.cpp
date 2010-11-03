#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 La gui è gestita a widget. Ogni volta che se ne mostra uno bisogna nascondere tutti gli altri.

 */

#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   caricaDb("dboggetti.db");



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




void MainWindow::caricaDb(char *nome)
{
    if( esisteDb(nome) )
        apriDb(nome);
    else
    {
        apriDb(nome);
        creaTabelle();
    }
}


bool MainWindow::esisteDb(char *nome)
{
    fstream fileIn;
    fileIn.open(nome, ios::in);
    if ( fileIn.is_open() )
    {
        fileIn.close();
        return true;
    }
    else
    {
        fileIn.close();
        return false;
    }
}

void MainWindow::creaTabelle()
{
    QSqlQuery creazione;
    QString query;

    query = "CREATE TABLE plastificazione (formati char(15), lucidabianca int, lucidabiancavolta int, opacabianca int, opacabiancavolta int)";
    creazione.prepare(query);
    creazione.exec();
    creazione.clear();
    query.clear();

    //Aggiungere qui le altre tabelle necessarie

}

void MainWindow::apriDb(char *nome)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(nome);
    database.open();
}




/*void MainWindow::visualizzaRicerca(QString nome)
{
    if (nome.isEmpty())
        queryModel.setQuery("SELECT * FROM oggetti");
    else
        queryModel.setQuery("SELECT * FROM oggetti WHERE nome = '"+nome+"'");
    queryModel.setHeaderData(0,Qt::Horizontal, "Nome");
    queryModel.setHeaderData(1, Qt::Horizontal, "Categoria");
    queryModel.setHeaderData(2, Qt::Horizontal, "Colore");
    queryModel.setHeaderData(3, Qt::Horizontal, "Posizione");
    queryModel.setHeaderData(4, Qt::Horizontal, "Associato A");
    queryModel.setHeaderData(5, Qt::Horizontal, "Quantita'");
    queryModel.setHeaderData(6, Qt::Horizontal, "Descrizione");
    ui->tableView->setModel(&queryModel);

}
*/
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

    refreshTabelle();
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

void MainWindow::refreshTabelle()
{
    QSqlTableModel *tabella_plastificazione = new QSqlTableModel;
    tabella_plastificazione->setTable("plastificazione");
    tabella_plastificazione->setEditStrategy(QSqlTableModel::OnFieldChange);
    tabella_plastificazione->select();
    tabella_plastificazione->setHeaderData(0, Qt::Horizontal, "Formati");
    tabella_plastificazione->setHeaderData(1, Qt::Horizontal, "Lucida Bianca");
    tabella_plastificazione->setHeaderData(2, Qt::Horizontal, "Lucida Bianca/Volta");
    tabella_plastificazione->setHeaderData(3, Qt::Horizontal, "Opaca Bianca");
    tabella_plastificazione->setHeaderData(4, Qt::Horizontal, "Opaca Bianca/Volta");
    ui->tableView_preventivi->setModel(tabella_plastificazione);

    //Aggiungere qui il refresh di altre tabelle
}

void MainWindow::on_bottone_plastificazione_aggiungi_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO plastificazione (formati, lucidabianca, lucidabiancavolta, opacabianca, opacabiancavolta)"
                  "VALUES(:formati, :lucidabianca, :lucidabiancavolta, :opacabianca, :opacabiancavolta) ") ;
    query.bindValue(":formati", "");
    query.bindValue(":lucidabianca", 0);
    query.bindValue(":lucidabiancavolta", 0);
    query.bindValue(":opacabianca", 0);
    query.bindValue(":opacabiancavolta", 0);
    query.exec();
    refreshTabelle();
}
